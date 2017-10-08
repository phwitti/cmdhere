#include "main.hpp"

#include <algorithm>
#include <string>

#include "../../shared/tolower.hpp"
#include "../../shared/stringconvert.hpp"
#include "../../shared/windows.hpp"

#include "com.hpp"
#include "folder_view.hpp"
#include "id_list.hpp"
#include "persist_folder_2.hpp"
#include "service_provider.hpp"
#include "shell_browser.hpp"
#include "shell_windows.hpp"
#include "web_browser_app.hpp"

extern "C" __declspec(dllexport) bool current_directory(
	char *_in_module_name, char *_in_class_name, void* _handle,
	char **_out_string, int _in_max_length
)
{
	const std::string c_sExplorerModuleName = "explorer.exe";
	const std::string c_sExplorerWClass = "ExplorerWClass";
	const std::string c_sCabinetWClass = "CabinetWClass";

	std::string sModuleName(_in_module_name);
	std::string sClassName(_in_class_name);

	typedef char out_string_t[];
	out_string_t *out_string = (out_string_t*)_out_string;

	if (pw::tolower(sModuleName) == c_sExplorerModuleName && (sClassName == c_sCabinetWClass || sClassName == c_sExplorerWClass))
	{
		try
		{
			auto com = pw::com::initialize();
			CComPtr<IShellWindows> shellwindows = com.create_instance<IShellWindows>();
			CComPtr<IWebBrowserApp> webbrowser;
			for (auto &dispatch : pw::shell_windows(shellwindows).to_vector<IDispatch>())
			{
				if (com.try_query_interface<IWebBrowserApp>(dispatch, &webbrowser.p) && pw::web_browser_app(webbrowser).hwnd() == (HWND)_handle)
				{
					CComPtr<IServiceProvider> serviceprovider = com.query_interface<IServiceProvider>(webbrowser);
					CComPtr<IShellBrowser> shellbrowser = pw::service_provider(serviceprovider).query_service<IShellBrowser>(SID_STopLevelBrowser);
					CComPtr<IShellView> shellview = pw::shell_browser(shellbrowser).active_shell_view();
					CComPtr<IFolderView> folderview = com.query_interface<IFolderView>(shellview);
					CComPtr<IPersistFolder2> persistfolder = pw::folder_view(folderview).folder<IPersistFolder2>();
					CComHeapPtr<ITEMIDLIST> itemidfolder = pw::persist_folder_2(persistfolder).current_folder();

					std::string path = pw::id_list(itemidfolder).path();
					std::size_t length = path.copy(*out_string, _in_max_length);
					_in_max_length = std::min(_in_max_length - 1, (int)length);
					(*out_string)[_in_max_length] = '\0';

					return true;
				}
			}

			return false;
		}
		catch (...)
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}