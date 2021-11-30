#include "demonstrationWidget.h"

inline void DemonstrationWidget::TableInformation::clear() {
   for (size_t *value : { &m_maxCollision, &m_numberOfSuccesses, &m_numberOfFailures } ) {
       *value = 0;
   }
   for (double *value : { &m_lastCoefficient, &m_maxCoefficient } ) {
       *value = 0;
   }
   for( auto *series : { m_pSeriesCoefficient, m_pSeriesNumberOfCollisions } ) {
        series->removePoints(0, series->count());
   }
    m_pSeriesNumberOfCollisions->append(0, 0);

   m_lastCoord = { 0, 0 };
   m_lastValue.front() = 0x0000;
   m_lastInsertion = false;
}

DemonstrationWidget::DemonstrationWidget(QWidget *pWidget)
    : QWidget                 ( pWidget )
    , m_pChartCoefficientView ( new QChartView(new QChart, this) )
    , m_pChartCollisionsView  ( new QChartView(new QChart, this) )
    , m_stop                  ( false   )
    , m_pStandardModel        ( nullptr )
    , m_pFunction             ( nullptr )
    , m_complicatedFunction   ( nullptr )
    , m_pAlgorithm            ( nullptr )
    , m_alphabetPower         ( '~' - ' ' + 1 )
    , m_pTable                ( nullptr )
    , m_tableInformation      ( new QLineSeries( m_pChartCoefficientView->chart() )
                              , new QLineSeries( m_pChartCollisionsView->chart() ) )
{
    setupUi(dynamic_cast<QWidget *>(this));

    m_tableView->horizontalHeader()->setSectionResizeMode( QHeaderView::ResizeToContents );
    QGridLayout *gridLayout = new QGridLayout;

    /*
     *  First chart
    */
    auto *axisX = new QValueAxis();
    auto *axisY = new QValueAxis();
    axisX->setTickCount(20);
    axisY->setTickCount(10);
    axisX->setRange( 1, 2 );
    axisY->setRange( 0, 1 );

    QChart *chartCoefficient = m_pChartCoefficientView->chart();
    chartCoefficient->setTitle( "The graph of change in the coefficient of simple uniform hashing" );
    chartCoefficient->legend()->hide();
    chartCoefficient->addAxis( axisX, Qt::AlignBottom );
    chartCoefficient->addAxis( axisY, Qt::AlignLeft );
    chartCoefficient->addSeries( m_tableInformation.m_pSeriesCoefficient );
    m_tableInformation.m_pSeriesCoefficient->attachAxis( axisX );
    m_tableInformation.m_pSeriesCoefficient->attachAxis( axisY );

    /*
     *  Second chart
    */

    axisX = new QValueAxis();
    axisY = new QValueAxis();
    axisX->setTickCount(20);
    axisY->setTickCount(10);
    axisX->setRange( 1, 2 );
    axisY->setRange( 0, 1 );

    QChart *chartCollision = m_pChartCollisionsView->chart();
    chartCollision->setTitle( "Graph of collision changes" );
    chartCollision->legend()->hide();
    chartCollision->addAxis( axisX, Qt::AlignBottom );
    chartCollision->addAxis( axisY, Qt::AlignLeft );
    chartCollision->addSeries( m_tableInformation.m_pSeriesNumberOfCollisions );
    m_tableInformation.m_pSeriesNumberOfCollisions->attachAxis( axisX );
    m_tableInformation.m_pSeriesNumberOfCollisions->attachAxis( axisY );

    /*
     * Views
    */

    m_pChartCoefficientView->installEventFilter(this);
    m_pChartCollisionsView->installEventFilter(this);

    m_pChartCoefficientView->setRubberBand(QChartView::RectangleRubberBand);
    m_pChartCollisionsView->setRubberBand(QChartView::RectangleRubberBand);

    m_pChartCoefficientView->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_pChartCollisionsView->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    m_pChartCoefficientView->setRenderHint(QPainter::Antialiasing);
    m_pChartCollisionsView->setRenderHint(QPainter::Antialiasing);

    m_pChartCoefficientView->setMinimumHeight(m_tableView->minimumHeight());
    m_pChartCollisionsView->setMinimumHeight(m_tableView->minimumHeight());

    /*
     *  Splitter
    */

    QSplitter *splitter = new QSplitter(Qt::Vertical);
    splitter->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    splitter->addWidget(m_tableView);
    splitter->addWidget(m_pChartCoefficientView);
    splitter->addWidget(m_pChartCollisionsView);

    gridLayout->addWidget(splitter, 0, 0, 1, 1);
    gridLayout->addWidget(m_rightScrollArea, 0, 1, 1, 1);
    gridLayout->addWidget(m_frmProgressBar, 1, 0, 1, 2);
    setLayout(gridLayout);

    /*
     *  Validator and HTML theory
    */

    m_leFrom->setValidator(new LatinValidator(m_leFrom));
    m_leInsert->setValidator(new LatinValidator(m_leInsert));

    /*
     *  HTML theory
    */

    connect( m_pbReset,      &QPushButton::clicked, this, &DemonstrationWidget::slotClickedReset      );
    connect( m_pbApply,      &QPushButton::clicked, this, &DemonstrationWidget::slotClickedApply      );
    connect( m_pbStatistics, &QPushButton::clicked, this, &DemonstrationWidget::slotClickedStatistics );
    connect( m_pbMakeItems,  &QPushButton::clicked, this, &DemonstrationWidget::slotClickedMakeItems  );
    connect( m_pbInsert,     &QPushButton::clicked, this, &DemonstrationWidget::slotClickedInsert     );
    connect( m_pbFindFree,   &QPushButton::clicked, this, &DemonstrationWidget::slotClickedFindFree   );
    connect( m_pbStop,       &QPushButton::clicked, this, &DemonstrationWidget::slotClickedStop       );
    connect( m_pbFocus,      &QPushButton::clicked, this, &DemonstrationWidget::slotClickedFocus      );

    connect( m_rbFNV1a32bit,          &QRadioButton::toggled, this, &DemonstrationWidget::slotUpdateAdditionalInputData );
    connect( m_rbPseudorandomProbing, &QRadioButton::toggled, this, &DemonstrationWidget::slotUpdateAdditionalInputData );
    connect( m_rbDoubleHashing,       &QRadioButton::toggled, this, &DemonstrationWidget::slotUpdateAdditionalInputData );
    connect( m_rbChains,              &QRadioButton::toggled, this, &DemonstrationWidget::slotUpdateAdditionalInputData );

    /*
     *  GUI
    */
    m_frmProgressBar->hide();
    m_frmFirstInputData->hide();
    m_frmSecondInputData->hide();
    m_gbInputData->hide();
}

/*
 *  Inserting elements
*/

void DemonstrationWidget::successfulInsertion(const table_type *, const value_type &value, std::pair<size_t, size_t> index, size_t numberOfCollisions) {
    m_tableInformation.m_lastCoord = index;
    m_tableInformation.m_lastValue = value;
    m_tableInformation.m_lastInsertion = true;
    ++m_tableInformation.m_numberOfSuccesses;

    m_tableInformation.m_lastCollision = numberOfCollisions;
    m_tableInformation.m_maxCollision = {
        numberOfCollisions > m_tableInformation.m_maxCollision
        ? numberOfCollisions
        : m_tableInformation.m_maxCollision
    };

//    m_tableInformation.m_lastCoefficient = simpleUniformHashingCoefficients;
//    if(simpleUniformHashingCoefficients > m_tableInformation.m_maxCoefficient) {
//        m_tableInformation.m_maxCoefficient = simpleUniformHashingCoefficients;
//    }

//    m_tableInformation.m_lastCollision = numberOfCollisions;
//    if(numberOfCollisions > m_tableInformation.m_maxCollision) {
//        m_tableInformation.m_maxCollision = simpleUniformHashingCoefficients;
//    }

//    m_tableInformation.m_pSeriesCoefficient->append(
//        m_tableInformation.m_numberOfSuccesses
//      , simpleUniformHashingCoefficients
//    );

    m_tableInformation.m_pSeriesNumberOfCollisions->append(
        m_tableInformation.m_numberOfSuccesses
      , numberOfCollisions
    );

    std::lock_guard<std::mutex> lk(m_columnUpdate);
    QModelIndex modelIndex = m_pStandardModel->index(index.first, index.second);
    if(getCurrentTableType() == TableType::Chain){
        updateColumns(index.first);
    }
    else {
        m_pStandardModel->setData( modelIndex, QVariant(toQString(value)) );
    }
}

void DemonstrationWidget::unsuccessfulInsertion(const table_type *, const value_type &value) {
    m_tableInformation.m_lastValue = value;
    m_tableInformation.m_lastInsertion = false;
    ++m_tableInformation.m_numberOfFailures;
}

inline void DemonstrationWidget::updateColumns(size_t rowIndex) {
    using namespace BusinessLogic::Hash::Table;

    auto tableRow = dynamic_cast<BusinessLogic::Hash::Table::Chains *>(m_pTable.get())->row(rowIndex);
    size_t modelColumnCount = m_pStandardModel->columnCount();
    size_t tableColumnCount = tableRow.size();

    if(modelColumnCount < tableColumnCount) {
        m_pStandardModel->insertColumns(
            modelColumnCount
          , std::max(tableColumnCount - modelColumnCount
                   , static_cast<size_t>(std::ceil(std::sqrt(m_tableInformation.m_lastCoefficient)))
            )
        );
    }

    QModelIndex modelIndex;
    auto iterator = tableRow.begin();
    for(size_t i = 0, size = tableRow.size(); i < size; ++i, ++iterator) {
        modelIndex = m_pStandardModel->index(rowIndex, i);
        m_pStandardModel->setData(
              modelIndex
            , QVariant(toQString(*iterator))
        );
    }
}

inline void DemonstrationWidget::updateCharts() {
    m_pChartCoefficientView->chart()->axes(Qt::Horizontal).front()->setRange(1, m_tableInformation.m_numberOfSuccesses);
    m_pChartCollisionsView->chart()->axes(Qt::Horizontal).front()->setRange(1, m_tableInformation.m_numberOfSuccesses);

    m_pChartCollisionsView->chart()->axes(Qt::Vertical).front()->setRange(0, m_tableInformation.m_maxCollision);
    m_pChartCoefficientView->chart()->axes(Qt::Vertical).front()->setRange(0, m_tableInformation.m_maxCoefficient);

    m_pChartCollisionsView->chart()->resetMatrix();
    m_pChartCoefficientView->chart()->resetMatrix();
}

inline void DemonstrationWidget::updateTableView() {
    m_tableView->scrollTo(
        m_pStandardModel->index(
            m_tableInformation.m_lastCoord.first
          , m_tableInformation.m_lastCoord.second
        )
      , QAbstractItemView::PositionAtCenter
    );
    m_tableView->repaint();
}

inline DemonstrationWidget::value_type &DemonstrationWidget::next(value_type &value) const {
       value[0] < endChar                        ? static_cast<void>(++value[0])
    : (value[0] = firstChar, value[1] < endChar) ? static_cast<void>(++value[1])
    : (value[1] = firstChar, value[2] < endChar) ? static_cast<void>(++value[2])
    : (value[2] = firstChar, value[3] < endChar) ? static_cast<void>(++value[3])
    : (value[3] = firstChar, value[4] < endChar) ? static_cast<void>(++value[4])
    :  static_cast<void>(value[4] = firstChar);

    return value;
}

inline void DemonstrationWidget::slotClickedMakeItems() {
    using namespace BusinessLogic::Convert;

    /*
     * Preparing
    */

    if(getCurrentTableType() == TableType::Chain && m_pStandardModel->columnCount() == 0) {
        m_pStandardModel->insertColumns(0, m_sbQuantity->value() / m_sbBucketQuantity->value());
    }

    m_frmProgressBar->setVisible(true);
    m_progressBar->setValue(0);

    /*
     * For other thread
    */

    std::atomic<size_t> progress(0);
    size_t target = m_sbQuantity->value();
    value_type currentString = toStdArray(m_leFrom->text().toStdString());

    setEnabledInsertingProcess(false);
    m_frmProgressBar->setVisible(true);

    std::packaged_task<void()> insertTask([&, this]() {
        while (++progress <= target) {
            m_pTable->insert(currentString);
            next(currentString);
            if(m_stop) {
                m_stop = false;
                break;
            }
        }

    });
    auto future = insertTask.get_future();

    auto differenceNumberOfSuccesses = m_tableInformation.m_numberOfSuccesses;
    auto differenceNumberOfFailures  = m_tableInformation.m_numberOfFailures;

    std::thread insertThread(std::move(insertTask));

    /*
     *  For main thread
    */

    int value;
    double div = static_cast<double>(m_progressBar->maximum()) / target;
    size_t partOfMaxProgressBar = m_progressBar->maximum() / 10;
    while (future.wait_for(std::chrono::milliseconds(0)) not_eq std::future_status::ready) {
        value = static_cast<int>(progress * div);
        if(value > m_progressBar->value()) {
            m_progressBar->setValue( value );
            if(value % partOfMaxProgressBar < 100) {
                updateCharts();
                updateTableView();
            }
        }
        std::lock_guard<std::mutex> lk(m_columnUpdate);
        QApplication::processEvents();
    }

    insertThread.join();
    updateCharts();
    updateTableView();

    m_frmProgressBar->setVisible(false);
    setEnabledInsertingProcess(true);

    /*
     *  Output message
    */

    differenceNumberOfSuccesses = m_tableInformation.m_numberOfSuccesses - differenceNumberOfSuccesses;
    differenceNumberOfFailures  = m_tableInformation.m_numberOfFailures - differenceNumberOfFailures;

    m_lblOutputMessages->setText(
        getColorTextHTML(QString("Successful inserts: %1").arg(differenceNumberOfSuccesses), "green") + "<br>"
      + getColorTextHTML(QString("Failed inserts&nbsp;&nbsp;&nbsp;&nbsp;: %1").arg(differenceNumberOfFailures), "red")
    );

}

inline void DemonstrationWidget::slotClickedInsert() {
    m_pTable->insert(toStdArray(m_leInsert->text().toStdString()));
    outputMessage(
         m_tableInformation.m_lastInsertion ? "Inserting is successful"
                                            : "The insertion has failed"
       , m_tableInformation.m_lastInsertion ? "green" : "red"
    );
}

/*
 *  Other logic
*/

inline auto DemonstrationWidget::getCurrentFactory() const {
    using namespace BusinessLogic::Hash;

    std::unique_ptr<const Factory::Abstract> factory;
    bool functionTypeIsFamily = getCurrentFunctionType() == RelationshipType::Family;
    if(getCurrentAlgorythmType() == RelationshipType::One) {
        factory = std::make_unique<Factory::One> (
              functionTypeIsFamily
              ? m_complicatedFunction // The complicated function must be prepared
              : std::dynamic_pointer_cast<Function::One::Creator>(m_pFunction)
            , std::dynamic_pointer_cast<Algorithm::One::Creator>(m_pAlgorithm)
        );
    }
    else if(functionTypeIsFamily) {
        factory = std::make_unique<Factory::Family> (
              std::dynamic_pointer_cast<Function::Family::Creator>(m_pFunction)
            , std::dynamic_pointer_cast<Algorithm::Family::Creator>(m_pAlgorithm)
        );
    }
    else {
        std::invalid_argument("function type not defined");
    }
    return factory;
}

inline void DemonstrationWidget::updateFunctionCreator() {
    using namespace BusinessLogic::Hash::Function;
    if(m_rbEquivalent->isChecked()) {
        m_pFunction = std::make_shared<Equivalent::Creator>();
    }
    else if(m_rbStandart->isChecked()) {
        m_pFunction = std::make_shared<Standart::Creator>();
    }
    else { // m_rbFNV1a32bit->isChecked()
        m_pFunction = std::make_shared<FNV1a::Creator>();
    }
}

inline void DemonstrationWidget::updateAlgorithmCreator() {
    using namespace BusinessLogic::Hash::Algorithm;
    if(m_rbLinearProbing->isChecked()) {
        m_pAlgorithm = std::make_shared<LinearProbing::Creator>();
    }
    else if(m_rbQuadraticProbing->isChecked()) {
        m_pAlgorithm = std::make_shared<QuadraticProbing::Creator>();
    }
    else if(m_rbPseudorandomProbing->isChecked()) {
        m_pAlgorithm = std::make_shared<PseudorandomProbing::Creator>(m_sbFirstInputData->value());
    }
    else { // m_rbDoubleHashing->isChecked()
        m_pAlgorithm = std::make_shared<DoubleHashing::Creator>(
              m_sbFirstInputData->value()
            , m_sbSecondInputData->value()
        );
    }
}

inline void DemonstrationWidget::deleteModel() {
    auto stringListModel = m_tableView->selectionModel();
    m_tableView->setModel(nullptr);
    if(stringListModel not_eq nullptr) {
        delete stringListModel;
    }
}

/*
 *  Table GUI
*/

inline void DemonstrationWidget::slotUpdateAdditionalInputData() {
    bool predicate = { getCurrentFunctionType() == RelationshipType::Family };
    m_gbInputData->setVisible(predicate);
    m_frmFirstInputData->setVisible(predicate);

    if(getCurrentTableType() == TableType::Chain) {
        m_rbStandart->setEnabled(true);
        m_frmSecondInputData->setVisible(false);
    }
    else if(getCurrentAlgorythmType() == RelationshipType::Family) {
        m_rbFNV1a32bit->setChecked(true);
        repaint();
        m_rbEquivalent->setDisabled(true);
        m_rbStandart->setDisabled(true);
        m_frmSecondInputData->setVisible(m_rbDoubleHashing->isChecked());
    }
    else {
        m_frmSecondInputData->setVisible(false);
    }
}

inline void DemonstrationWidget::slotClickedApply() {
    using namespace BusinessLogic::Hash;
    using namespace BusinessLogic::Hash::Function::Pattern;

    if(   m_rbDoubleHashing->isChecked()
       && m_sbFirstInputData->value() == m_sbSecondInputData->value() )
    {
        outputMessage("Hash function coefficients should not match", "red");
        return;
    }

    setEnabledCreateHashTable(false);
    m_pbFocus->setEnabled(true);

    updateFunctionCreator();
    updateAlgorithmCreator();

    bool tableTypeIsChain = getCurrentTableType() == TableType::Chain;
    bool functionTypeIsFamily = getCurrentFunctionType() == RelationshipType::Family;

    size_t bucketQuantity = m_sbBucketQuantity->value();
    if(functionTypeIsFamily
       && (tableTypeIsChain || getCurrentAlgorythmType() == RelationshipType::One)
    ) {
        m_complicatedFunction = std::make_shared<FamilyToOne::Creator>(
            std::dynamic_pointer_cast<Function::Family::Creator>(m_pFunction), m_sbFirstInputData->value()
        );
    }

    if(tableTypeIsChain) {
        m_pTable = std::make_unique<Table::Chains>(
              bucketQuantity
            , functionTypeIsFamily
              ? *m_complicatedFunction
              : *std::dynamic_pointer_cast<Function::One::Creator>(m_pFunction)
            , m_alphabetPower
        );
    }
    else {
        auto factory = getCurrentFactory();
        m_pTable = std::make_unique<Table::OpenAddressing>(bucketQuantity, *factory, m_alphabetPower);
    }
    m_pTable->signTheObject(this);

    /*
    *  A descendant will notify an ancestor of his own destruction when using delete
    */
    deleteModel();
    m_pStandardModel = new QStandardItemModel(bucketQuantity, (tableTypeIsChain ? 0 : 1), this);
    m_tableView->setModel(m_pStandardModel);

    m_lblOutputMessages->setText(getColorTextHTML("The model was created", "green"));
}

inline void DemonstrationWidget::slotClickedStatistics() const {
    QMessageBox::information(nullptr, "Statistics"
        , QString("Maximum number of collisions:\t%1\n").arg(m_tableInformation.m_maxCollision)
        + QString("Number of successful inserts:\t\t%1\n").arg(m_tableInformation.m_numberOfSuccesses)
        + QString("Number of failed inserts:\t\t%1\n").arg(m_tableInformation.m_numberOfFailures)
        + QString("Simple uniform hashing coefficient:\t%1\n").arg(m_tableInformation.m_lastCoefficient)
    );
}

inline void DemonstrationWidget::slotClickedFindFree() {
    value_type currentString = m_tableInformation.m_lastValue;
    while(m_pTable->isExist(next(currentString))) continue;
    QString result = toQString(currentString);
    m_leFrom->setText(result);
    m_leInsert->setText(result);
}

inline void DemonstrationWidget::slotClickedStop() {
    m_stop = true;
    setEnabledInsertingProcess(true);
}

inline void DemonstrationWidget::slotClickedFocus() {
    updateCharts();
}

/*
 *  Base GUI
*/

inline void DemonstrationWidget::slotClickedReset() {
    setEnabledCreateHashTable(true);
    m_pbFocus->setDisabled(true);

    m_complicatedFunction.reset();
    m_pTable.release();
    m_tableInformation.clear();
    resetAxes();
    deleteModel();

    outputMessage("The model has been deleted", "green");
}

inline QString DemonstrationWidget::getColorTextHTML(const QString &text, const char * const color) const {
    return QString(m_fontBeginColorHTML).arg(color) + text + m_fontEndHTML;
}

inline void DemonstrationWidget::outputMessage(const QString &text, const char * const color) {
    m_lblOutputMessages->setText(getColorTextHTML(text, color));
}

inline void DemonstrationWidget::setEnabledCreateHashTable(bool flag) {
    for (QWidget *widget : std::initializer_list<QWidget *>{
        m_pbApply
        , m_sbBucketQuantity
        , m_gbResolutionOfCollisions
        , m_gbFunction
        , m_gbInputData
    }) {
        widget->setEnabled(flag);
    }

    if(getCurrentTableType() not_eq TableType::Chain) {
        m_gbAlgorithm->setEnabled(flag);
    }
    m_gbLoadTable ->setDisabled(flag);
    m_pbStatistics->setDisabled(flag);
}

inline void DemonstrationWidget::setEnabledInsertingProcess(bool flag) {
    for (QWidget *widget : std::initializer_list<QWidget *>{
        m_leFrom
        , m_sbQuantity
        , m_pbMakeItems
        , m_leInsert
        , m_pbInsert
        , m_pbReset
        , m_pbStatistics
    }) {
        widget->setEnabled(flag);
    }
    m_pbStop->setDisabled(flag);
}
