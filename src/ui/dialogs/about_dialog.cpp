#include "about_dialog.h"

#include "base/resources.h"
#include "base/strings/string_util.h"

#include <format>

ui::internal::AboutDialog::AboutDialog(wxWindow *parent) : AboutDialogBase(parent)
{
    const auto author = wxT("rh2357a (rh2357a@gmail.com)");
    m_authorText->SetLabel(author);

    const auto version = std::format("버전: {}", APP_VERSION_STR);
    m_versionText->SetLabel(wxString::FromUTF8(version));

    const auto appVersionHtml = embed::GetAppVersionsHtml();
    m_versionHtml->SetPage(base::ToWxString(appVersionHtml));

    const auto appThirdPartyNotices = embed::GetAppThirdPartyNotices();
    m_thirdPartyNoticesText->SetValue(base::ToWxString(appThirdPartyNotices));
    m_thirdPartyNoticesText->Bind(wxEVT_CONTEXT_MENU, [this](...) { /* 오른쪽 메뉴 방지 */ });
}

void ui::ShowAboutDialog(wxWindow *parent)
{
    internal::AboutDialog dialog(parent);
    dialog.ShowModal();
}
