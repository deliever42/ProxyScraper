#include <iostream>
#include <windows.h>
#include <fstream>
#include <wininet.h>
#pragma comment(lib, "wininet.lib")

using namespace std;

const char* httpProxyList[] = {
    "https://api.proxyscrape.com/?request=displayproxies&proxytype=http",
    "https://www.proxy-list.download/api/v1/get?type=http",
    "https://www.proxyscan.io/download?type=http",
    "https://api.openproxylist.xyz/http.txt",
    "https://raw.githubusercontent.com/TheSpeedX/PROXY-List/master/http.txt",
    "https://raw.githubusercontent.com/ShiftyTR/Proxy-List/master/http.txt",
    "https://raw.githubusercontent.com/jetkai/proxy-list/main/online-proxies/txt/proxies-http.txt",
    "https://raw.githubusercontent.com/mertguvencli/http-proxy-list/main/proxy-list/data.txt"
};

const char* socks4ProxyList[] = {
    "https://api.proxyscrape.com/?request=displayproxies&proxytype=socks4",
    "https://raw.githubusercontent.com/jetkai/proxy-list/main/online-proxies/txt/proxies-socks4.txt",
    "https://www.proxy-list.download/api/v1/get?type=socks4",
    "https://www.proxyscan.io/download?type=socks4",
    "https://api.openproxylist.xyz/socks4.txt",
    "https://raw.githubusercontent.com/ShiftyTR/Proxy-List/master/socks4.txt",
    "https://raw.githubusercontent.com/TheSpeedX/PROXY-List/master/socks4.txt"
};

const char* socks5ProxyList[] = {
    "https://api.proxyscrape.com/?request=displayproxies&proxytype=socks5",
    "https://www.proxy-list.download/api/v1/get?type=socks5",
    "https://www.proxyscan.io/download?type=socks5",
    "https://raw.githubusercontent.com/ShiftyTR/Proxy-List/master/socks5.txt",
    "https://raw.githubusercontent.com/jetkai/proxy-list/main/online-proxies/txt/proxies-socks5.txt",
    "https://api.openproxylist.xyz/socks5.txt",
    "https://raw.githubusercontent.com/TheSpeedX/PROXY-List/master/socks5.txt"
};

void downloadProxyList(const char* url, const char* path) {
	HINTERNET hInternet = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	HINTERNET hFile = InternetOpenUrlA(hInternet, url, NULL, 0, INTERNET_FLAG_RELOAD, 0);
   
    if (hFile) {
        ofstream file(path);
        char buffer[1024];
        DWORD bytesRead;
        
        while (InternetReadFile(hFile, buffer, sizeof(buffer), &bytesRead) && bytesRead) {
            file.write(buffer, bytesRead);
        }
        
        file.close();
        InternetCloseHandle(hFile);
    }
}

int main()
{
    cout << "[+] Downloading HTTP Proxies" << endl;
	for (auto url : httpProxyList) {
		downloadProxyList(url, "http.txt");
	}

	cout << "[+] Downloading SOCKS4 Proxies" << endl;
	for (auto url : socks4ProxyList) {
		downloadProxyList(url, "socks4.txt");
	}

	cout << "[+] Downloading SOCKS5 Proxies" << endl;
	for (auto url : socks5ProxyList) {
		downloadProxyList(url, "socks5.txt");
	}

	cout << "[+] Done" << endl;
    Sleep(3000);
}