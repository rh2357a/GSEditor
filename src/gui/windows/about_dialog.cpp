#include "about_dialog.h"

#include "resources.h"
#include "embed.h"
#include "utils.h"

#include <string>
#include <format>

gui::windows::AboutDialog::AboutDialog(wxWindow *parent) : AboutDialogBase(parent)
{
    m_authorText->SetLabel(wxT("rh2357a (rh2357a@gmail.com)"));

    const auto version = std::format("버전: {}", APP_VERSION_STR);
    m_versionText->SetLabel(wxString::FromUTF8(version));

    const auto &html = utils::strings::to_wx_string(embed::app_version_html);
    m_versionHtml->SetPage(html);

    const auto &openSourceLicenses = utils::strings::to_wx_string(embed::open_source_licenses_txt);
    m_openSourceLicensesText->SetValue(openSourceLicenses);
    m_openSourceLicensesText->Bind(wxEVT_CONTEXT_MENU, [this](...) { /* 오른쪽 메뉴 방지 */ });
}
