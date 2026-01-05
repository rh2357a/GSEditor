#include "about_dialog.h"

#include "embed.h"
#include "utils.h"

gui::windows::AboutDialog::AboutDialog(wxWindow *parent) : AboutDialogBase(parent)
{
    const auto &html = utils::strings::to_wx_string(embed::app_version_html);
    m_versionHtml->SetPage(html);

    m_authorText->SetLabel(wxT("rh2357a (rh2357a@gmail.com)"));
    m_versionText->SetLabel(wxT("버전: 1.2.8.0"));
}
