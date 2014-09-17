#include "permissions.h"

namespace VPZ {
namespace APKStudio {
namespace Dialog {

void Permissions::initialize()
{
    /*
     * @Initialize
     */
    // Bottons
    QDialogButtonBox *box = new QDialogButtonBox(this);
    // Button
    this->_cancel = new QPushButton(text("label_cancel"), box);
    this->_change = new QPushButton(text("label_change"), box);
    // Group
    QGroupBox *group = new QGroupBox(text("label_group"), this);
    QGroupBox *owner = new QGroupBox(text("label_owner"), this);
    QGroupBox *world = new QGroupBox(text("label_world"), this);
    // Checkbox
    this->_gr = new QCheckBox(text("label_read"), group);
    this->_gw = new QCheckBox(text("label_write"), group);
    this->_gx = new QCheckBox(text("label_execute"), group);
    this->_or = new QCheckBox(text("label_read"), owner);
    this->_ow = new QCheckBox(text("label_write"), owner);
    this->_ox = new QCheckBox(text("label_execute"), owner);
    this->_recursive = new QCheckBox(text("label_recursive"), this);
    this->_wr = new QCheckBox(text("label_read"), world);
    this->_ww = new QCheckBox(text("label_write"), world);
    this->_wx = new QCheckBox(text("label_execute"), world);
    // Layout
    QVBoxLayout *main = new QVBoxLayout(this);
    QHBoxLayout *grid = new QHBoxLayout();
    QVBoxLayout *groups = new QVBoxLayout(group);
    QVBoxLayout *owners = new QVBoxLayout(owner);
    QVBoxLayout *worlds = new QVBoxLayout(world);
    /*
     * @Prepare
     */
    // Checkbox
    this->_gr->setChecked(this->_file.permission.group.read);
    this->_gw->setChecked(this->_file.permission.group.write);
    this->_gx->setChecked(this->_file.permission.group.execute);
    this->_or->setChecked(this->_file.permission.owner.read);
    this->_ow->setChecked(this->_file.permission.owner.write);
    this->_ox->setChecked(this->_file.permission.owner.execute);
    this->_wr->setChecked(this->_file.permission.world.read);
    this->_ww->setChecked(this->_file.permission.world.write);
    this->_wx->setChecked(this->_file.permission.world.execute);
    // Group
    group->setMinimumWidth(140);
    group->setLayout(groups);
    owner->setMinimumWidth(140);
    owner->setLayout(owners);
    world->setMinimumWidth(140);
    world->setLayout(worlds);
    // Window
    this->resize(QSize(420, 192));
    this->setMinimumSize(QSize(240, 160));
#ifdef Q_OS_WIN
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
#endif
    this->setWindowIcon(icon("window"));
    this->setWindowTitle(text("title_window"));
    /*
     * @Inflate
     */
    // Buttons
    box->addButton(this->_cancel, QDialogButtonBox::RejectRole);
    box->addButton(this->_change, QDialogButtonBox::AcceptRole);
    // Checkboxes
    groups->addWidget(this->_gr);
    groups->addWidget(this->_gw);
    groups->addWidget(this->_gx);
    owners->addWidget(this->_or);
    owners->addWidget(this->_ow);
    owners->addWidget(this->_ox);
    worlds->addWidget(this->_wr);
    worlds->addWidget(this->_ww);
    worlds->addWidget(this->_wx);
    // Layout
    grid->addWidget(owner);
    grid->addWidget(group);
    grid->addWidget(world);
    main->addLayout(grid);
    main->addWidget(this->_recursive);
    main->addWidget(box);
    /*
     * @Bind
     */
    this->connect(this->_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    this->connect(this->_change, SIGNAL(clicked()), this, SLOT(__accept()));
    /*
     * @Assign
     */
    // Recursive
    if (!((this->_file.type == Bridge::File::DIRECTORY) || (this->_file.type == Bridge::File::SYMLINK_DIRECTORY)))
        this->_recursive->setEnabled(false);
    // Window
    this->setLayout(main);
}

} // namespace Dialog
} // namespace APKStudio
} // namespace VPZ
