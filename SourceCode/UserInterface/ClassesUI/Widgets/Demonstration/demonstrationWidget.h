#ifndef DEMONSTRATION_WIDGET_H
#define DEMONSTRATION_WIDGET_H

#include "ui_demonstrationWidget.h"
#include "hashTable.h"
#include "SourceCode/BusinessLogic/businessLogic.h"
#include "SourceCode/BusinessLogic/hashHeaderFiles.h"
#include "../../Validator/validator.h"

#include <memory>
#include <array>
#include <algorithm>
#include <thread>

#include <QStringListModel>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>

class DemonstrationWidget : public QWidget
                          , protected Ui::DemonstrationWidget
                          , public BusinessLogic::Hash::Table::Pattern::InterfaceSubscriber
{
public:
    using value_type = BusinessLogic::Hash::Table::Abstract::value_type;
    using table_type = BusinessLogic::Hash::Table::Abstract;

private:
    struct TableInformation {
    public:
        /* Qt containers */
        QLineSeries *m_pSeriesNumberOfCollisions;

        /* If successful */
        std::pair<size_t, size_t> m_lastCoord;
        size_t       m_numberOfSuccesses;
        size_t       m_lastCollision;
        size_t       m_maxCollision;
        double       m_lastCoefficient;
        double       m_maxCoefficient;

        /* If unsuccessful */
        size_t      m_numberOfFailures;

        /* In any case */
        value_type  m_lastValue;
        bool        m_lastInsertion;

    public:
        TableInformation(const TableInformation &) = delete;
        TableInformation(TableInformation &&) = delete;

        TableInformation(QLineSeries *maxCollision )
            : m_pSeriesNumberOfCollisions( maxCollision )
        {
            clear();
        };

    public:
        void clear();
    };

private: // Event filter
    virtual bool eventFilter( QObject *target, QEvent *event ) override {
        if ( target == m_pChartCollisionsView ) {
            QChartView *view = dynamic_cast<QChartView *>( target );
            QChart *chart = view->chart();

            switch( event->type() ) {
                case QEvent::Wheel: {
                    QWheelEvent *currentEvent = dynamic_cast<QWheelEvent *>( event );

                    qreal factor = currentEvent->angleDelta().y() > 0 ? 0.9 : 1.1;
                    QRectF rect = QRectF(  chart->plotArea().left()
                                         , chart->plotArea().top()
                                         , chart->plotArea().width() * factor
                                         , chart->plotArea().height() * factor
                    );

                    QPointF mousePos = view->mapFromGlobal(QCursor::pos());
                    rect.moveCenter(mousePos);
                    chart->zoomIn(rect);

                    QPointF delta = chart->plotArea().center() - mousePos;
                    chart->scroll( delta.x(), -delta.y() );

                    return true;
                } break;
                default: {
                    return false;
                } break;
            }
        }
        return false;
    }

public:
    enum class TableType : short {
        Chain, OpenAdressing, Indefined
    };
    enum class RelationshipType : short {
        One, Family, Indefined
    };

private:
    /*
     *  Constants
    */
    static constexpr char firstChar = '!';
    static constexpr char endChar   = '~';

     QChartView *m_pChartCollisionsView;
     QStandardItemModel *m_pStandardModel;
     bool m_stop;

    /*
    *  Business logic
    */
     std::shared_ptr<BusinessLogic::Hash::Function::Abstract::Creator>  m_pFunction;
     std::shared_ptr<BusinessLogic::Hash::Function::One::Creator>       m_complicatedFunction;
     std::shared_ptr<BusinessLogic::Hash::Algorithm::Abstract::Creator> m_pAlgorithm;
     size_t m_alphabetPower;
     std::unique_ptr<BusinessLogic::Hash::Table::Abstract> m_pTable;
     TableInformation m_tableInformation;

     /*
     *  HTML tags
     */
     static constexpr auto m_fontBeginColorHTML = R"(<font color="%1">)";
     static constexpr auto m_fontEndHTML        = R"(</font>)";

public:
    DemonstrationWidget(QWidget *pWidget = nullptr);

public: // Custom slots
    virtual void successfulInsertion(const table_type *, const value_type &, std::pair<size_t, size_t>, size_t) override;
    virtual void unsuccessfulInsertion(const table_type *, const value_type &) override;
    virtual void filledInPart(const table_type *) override {};

private:
    /*
     * Business logic
    */
    TableType        getCurrentTableType() const {
        TableType result;
        result = {   m_rbChains->isChecked()        ? TableType::Chain
                   : m_rbOpenAdressing->isChecked() ? TableType::OpenAdressing
                                                    : TableType::Indefined
        };
        if(result == TableType::Indefined) {
            throw std::invalid_argument("table not defined");
        }
        return result;
    }
    RelationshipType getCurrentFunctionType() const {
        RelationshipType result;
        result = {   m_rbEquivalent->isChecked() ? RelationshipType::One
                   : m_rbStandart->isChecked()   ? RelationshipType::One
                   : m_rbFNV1a32bit->isChecked() ? RelationshipType::Family
                                                 : RelationshipType::Indefined
        };
        if(result == RelationshipType::Indefined) {
            throw std::invalid_argument("function not defined");
        }
        return result;

    }
    RelationshipType getCurrentAlgorythmType() const {
        RelationshipType result;
        result = {   m_rbLinearProbing->isChecked()       ? RelationshipType::One
                   : m_rbQuadraticProbing->isChecked()    ? RelationshipType::One
                   : m_rbPseudorandomProbing->isChecked() ? RelationshipType::Family
                   : m_rbDoubleHashing->isChecked()       ? RelationshipType::Family
                                                          : RelationshipType::Indefined
        };
        if(result == RelationshipType::Indefined) {
            throw std::invalid_argument("algorythm not defined");
        }
        return result;
    }

    auto getCurrentFactory() const;
    void updateFunctionCreator();
    void updateAlgorithmCreator();
    void deleteModel();
    void resetAxes() {
        m_pChartCollisionsView->chart()->axes(Qt::Horizontal).front()->setRange(1, 2);
        m_pChartCollisionsView->chart()->axes(Qt::Vertical).front()->setRange(0, 1);
    }
    QString toQString(const value_type &value) {
        auto convert = value;
        unsigned size = std::remove(convert.begin(), convert.end(), '\0') - convert.begin();
        return QString::fromLatin1(convert.data(), size);
    }
    value_type toStdArray(std::string &&value) const {
        value_type result = { '\0', '\0', '\0', '\0', firstChar };
        std::copy(value.rbegin(), value.rend(), result.rbegin());
        return result;
    }
    value_type &next(value_type &value) const;
    bool checkBeforeInsertion(bool);

    /*
    *   GUI and displaying
    */
    QString getColorTextHTML(const QString &text, const char * const color) const;
    void outputMessage(const QString &text, const char * const color);
    void updateColumns(size_t rowIndex);
    void updateCharts();
    void updateTableView();
    void setEnabledCreateHashTable(bool flag);
    void setEnabledInsertingProcess(bool flag);

public slots:
    void slotTabSwitched(int index) {
        if(index == 1) {
            QSplitter *splitter = findChild<QSplitter *>("");
            auto children = splitter->children();
            QList<int> sizes {
                dynamic_cast<QWidget *>(children[0])->minimumHeight()
                , dynamic_cast<QWidget *>(children[1])->minimumHeight()
            };
            splitter->setSizes(sizes);
        }
    }

private slots:
    void slotUpdateAdditionalInputData();
    void slotClickedReset();
    void slotClickedApply();
    void slotClickedMakeItems();
    void slotClickedInsert();
    void slotClickedStatistics();
    void slotClickedFindFree();
    void slotClickedStop();
    void slotClickedFocus();
};

#endif // DEMONSTRATION_WIDGET_H
