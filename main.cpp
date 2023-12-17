#include <windows.h>
#include "addy.h"
#include <string>

HWND g_hTextbox;
HWND g_hText;
HWND g_inject;
HWND g_execute;
bool g_buttonClicked = false;
const char *hello;
const char *syntax;
const char *hi;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "hack";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Minetest Hack - espero_dev",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 200,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    g_hTextbox = CreateWindowEx(
        0,
        "EDIT",
        "",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        10, 10, 200, 25,
        hwnd, NULL, hInstance, NULL
    );

    /*g_hText = CreateWindowEx(
        0,
        "EDIT",
        "",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        10, 10, 200, 25,
        hwnd, NULL, hInstance, NULL
    );*/

    g_execute = CreateWindow(
        "BUTTON",
        "Execute",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        220, 10, 25, 25,
        hwnd, NULL, hInstance, NULL
    );

    g_inject = CreateWindow(
        "BUTTON",
        "Inject",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        220, 30, 25, 25,
        hwnd, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (g_buttonClicked) {
            char loser[256];
            GetWindowText(g_hTextbox, loser, sizeof(loser));
            char* openingParenthesisPosition = strchr(loser, '(');

            if (openingParenthesisPosition != NULL) {
                char* closingParenthesisPosition = strchr(openingParenthesisPosition, ')');

                if (closingParenthesisPosition != NULL) {
                    size_t startPos = openingParenthesisPosition - loser + 1;
                    size_t endPos = closingParenthesisPosition - loser;
                    size_t length = endPos - startPos;

                    if (length > 0 && startPos + length < sizeof(loser)) {
                        char extractedText[256];
                        strncpy(extractedText, loser + startPos, length);
                        extractedText[length] = '\0';
                        hello = loser;
                        //MessageBox(NULL, extractedText, "Extracted Text", MB_OK);
                    }
                }
            } else {
                //MessageBox(NULL, "No opening parenthesis found.", "Text Analysis", MB_OK);
            }
            g_buttonClicked = false;

            char buffer[256];
            GetWindowText(g_hTextbox, buffer, sizeof(buffer));
            char* semicolonPosition = strchr(buffer, '(');

            if (semicolonPosition != NULL) {
                size_t semicolonIndex = semicolonPosition - buffer;
                size_t len = strlen(buffer);

                for (size_t i = semicolonIndex + 2, j = semicolonIndex + 3; j <= len; ++i, ++j) {
                    buffer[i] = buffer[j];
                }

                syntax = buffer;
                //MessageBox(NULL, buffer, "Modified Text", MB_OK);
            } else {
                //MessageBox(NULL, "No semicolon found.", "Text Analysis", MB_OK);
            }
            g_buttonClicked = false;
        }
    }

    return 0;
}

/*DWORD WINAPI FuckYou(PVOID lvpParameter)
{
    string WholeScript = "";
	HANDLE hPipe;
	char buffer[999999];
	DWORD dwRead;
	hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\ScriptExecution"),
		PIPE_ACCESS_DUPLEX | PIPE_TYPE_BYTE | PIPE_READMODE_BYTE,
		PIPE_WAIT,
		1,
		999999,
		999999,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);
	while (hPipe != INVALID_HANDLE_VALUE)
	{
		if (ConnectNamedPipe(hPipe, NULL) != FALSE)
		{
			while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL) != FALSE)
			{
				buffer[dwRead] = '\0';
				try {
					try {
						WholeScript = WholeScript + buffer;
					}
					catch (...) {
					}
				}
				catch (std::exception e) {

				}
				catch (...) {

				}
			}
            Execute("SSKA", "1.34");
            //Execute();
			//Wrapper::Execute_Script(WholeScript);
			WholeScript = "";
		}
		DisconnectNamedPipe(hPipe);
	}
}*/

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_COMMAND:
            if (HIWORD(wParam) == BN_CLICKED) {
                if ((HWND)lParam == g_execute) {
                    Execute(syntax, hello);
                    g_buttonClicked = true;
                }
                if ((HWND)lParam == g_inject) {
                    // creates a thread
                    //CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)FuckYou, NULL, NULL, NULL);
                    MessageBox(NULL, "Injected", "You hav been injected", MB_OK);
                }
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}