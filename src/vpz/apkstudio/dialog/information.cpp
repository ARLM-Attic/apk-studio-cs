#include "information.h"

namespace VPZ {
namespace APKStudio {
namespace Dialog {

void Information::initialize()
{
    /*
     * @Initialize
     */
    // Group
    this->_hardware = new QGroupBox(text("label_hardware"), this);
    this->_network = new QGroupBox(text("label_network"), this);
    this->_software = new QGroupBox(text("label_software"), this);
    // Hardware
    this->_board = new QLineEdit(this->_hardware);
    this->_cpu = new QLineEdit(this->_hardware);
    this->_imei = new QLineEdit(this->_hardware);
    this->_manufacturer = new QLineEdit(this->_hardware);
    this->_model = new QLineEdit(this->_hardware);
    this->_secure = new QLineEdit(this->_hardware);
    // Layout
    QGridLayout *grid = new QGridLayout(this);
    QFormLayout *hardware = new QFormLayout(this->_hardware);
    QFormLayout *network = new QFormLayout(this->_network);
    QFormLayout *software = new QFormLayout(this->_software);
    // Network
    this->_country = new QLineEdit(this->_network);
    this->_operator = new QLineEdit(this->_network);
    this->_timezone = new QLineEdit(this->_network);
    this->_type = new QLineEdit(this->_network);
    // Software
    this->_build = new QLineEdit(this->_software);
    this->_date = new QLineEdit(this->_software);
    this->_fingerprint = new QLineEdit(this->_software);
    this->_sdk = new QLineEdit(this->_software);
    this->_tags = new QLineEdit(this->_software);
    this->_version = new QLineEdit(this->_software);
    /*
     * @Prepare
     */
    // Window
#ifdef Q_OS_WIN
    this->resize(QSize(480, 360));
#else
    this->resize(QSize(640, 480));
#endif
    this->setMinimumSize(QSize(320, 240));
    this->setMaximumSize(QSize(800, 600));
#ifdef Q_OS_WIN
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
#endif
    this->setWindowIcon(icon("window"));
    this->setWindowTitle(text("title_window").arg(this->_device));
    // Textbox
    this->_board->setReadOnly(true);
    this->_cpu->setReadOnly(true);
    this->_imei->setReadOnly(true);
    this->_manufacturer->setReadOnly(true);
    this->_model->setReadOnly(true);
    this->_secure->setReadOnly(true);
    this->_country->setReadOnly(true);
    this->_operator->setReadOnly(true);
    this->_timezone->setReadOnly(true);
    this->_type->setReadOnly(true);
    this->_build->setReadOnly(true);
    this->_date->setReadOnly(true);
    this->_fingerprint->setReadOnly(true);
    this->_sdk->setReadOnly(true);
    this->_tags->setReadOnly(true);
    this->_version->setReadOnly(true);
    /*
     * @Inflate
     */
    // Grid
    grid->addWidget(this->_hardware, 0, 0);
    grid->addWidget(this->_network, 0, 1);
    grid->addWidget(this->_software, 1, 0, 1, 2);
    // Hardware
    hardware->addRow(text("label_manufacturer"), this->_manufacturer);
    hardware->addRow(text("label_model"), this->_model);
    hardware->addRow(text("label_imei"), this->_imei);
    hardware->addRow(text("label_board"), this->_board);
    hardware->addRow(text("label_cpu"), this->_cpu);
    hardware->addRow(text("label_secure"), this->_secure);
    // Network
    network->addRow(text("label_type"), this->_type);
    network->addRow(text("label_country"), this->_country);
    network->addRow(text("label_operator"), this->_operator);
    network->addRow(text("label_timezone"), this->_timezone);
    // Software
    software->addRow(text("label_version"), this->_version);
    software->addRow(text("label_sdk"), this->_sdk);
    software->addRow(text("label_build"), this->_build);
    software->addRow(text("label_fingerprint"), this->_fingerprint);
    software->addRow(text("label_date"), this->_date);
    software->addRow(text("label_tags"), this->_tags);
    /*
     * @Assign
     */
    // Grid
    this->setLayout(grid);
    // Group
    this->_hardware->setLayout(hardware);
    this->_network->setLayout(network);
    this->_software->setLayout(software);
    // Register
    qRegisterMetaType<QMap<QString, QString> >("QMap<QString, QString>");
}

void Information::retrieve()
{
    /*
     * @Build
     */
    // Prepare
    Runtime::Build *build = new Runtime::Build(this->_device);
    // Bind
    this->connect(build, SIGNAL(build(const QMap<QString, QString> &)), this, SLOT(__build(const QMap<QString, QString> &)));
    // Execute
    build->start();
    /*
     * @IMEI
     */
    // Prepare
    Runtime::IMEI *imei = new Runtime::IMEI(this->_device);
    // Bind
    this->connect(imei, SIGNAL(imei(const QString &)), this, SLOT(__imei(const QString &)));
    // Execute
    imei->start();
}

void Information::__build(const QMap<QString, QString> &information)
{
    // Hardware
    this->_board->setText(information.value(QString("ro.product.board")));
    this->_cpu->setText(information.value(QString("ro.product.cpu.abi")));
    QString manufacturer = information.value(QString("ro.product.manufacturer"));
    this->_manufacturer->setText(Utility::Text::capitalize(manufacturer));
    this->_model->setText(information.value(QString("ro.product.model")));
    this->_secure->setText(information.value(QString("ro.secure")));
    // Network
    QString country = information.value(QString("gsm.sim.operator.iso-country"));
    this->_country->setText(country.toUpper());
    QString operator_ = information.value(QString("gsm.sim.operator.alpha"));
    this->_operator->setText(Utility::Text::capitalize(operator_, true));
    this->_timezone->setText(information.value(QString("persist.sys.timezone")));
    this->_type->setText(information.value(QString("gsm.network.type")));
    // Software
    this->_build->setText(information.value(QString("ro.build.description")));
    int seconds = information.value(QString("ro.build.date.utc")).toInt();
    this->_date->setText(Utility::Format::time(QDateTime::fromTime_t(seconds)));
    this->_fingerprint->setText(information.value(QString("ro.build.fingerprint")));
    this->_sdk->setText(information.value(QString("ro.build.version.sdk")));
    this->_tags->setText(information.value(QString("ro.build.tags")));
    this->_version->setText(information.value(QString("ro.build.version.release")));
}

void Information::__imei(const QString &imei)
{
    this->_imei->setText(imei);
}

} // namespace Dialog
} // namespace APKStudio
} // namespace VPZ
