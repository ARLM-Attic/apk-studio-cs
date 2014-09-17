#include "ui.h"

namespace VPZ {
namespace APKStudio {
namespace Utility {

void UI::button(QPushButton *button)
{
    QSize size = button->fontMetrics().size(Qt::TextShowMnemonic, button->text());
    size.setWidth(size.width() + 12);
    QStyleOptionButton option;
    option.initFrom(button);
    option.rect.setSize(size);
    button->setMaximumSize(button->style()->sizeFromContents(QStyle::CT_PushButton, &option, size, button));
}

} // namespace Utility
} // namespace APKStudio
} // namespace VPZ
