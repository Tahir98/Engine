#pragma once

#include <d3d11.h>
#include <exception>
#include <cstdio>
#include <wrl.h>
#include <comdef.h>
#include <atlstr.h>

namespace DX
{
    class Direct3D11
    {
        // Helper class for COM exceptions
        class com_exception : public std::exception
        {
        public:
            com_exception(HRESULT hr) : result(hr) {}

            const char* what() const noexcept override
            {
                _com_error err(result);
                LPCTSTR errMsg = err.ErrorMessage();

            
                CStringA sB(errMsg);
                const char* pszC = sB;
                char* pszD = const_cast<char*>(pszC);

                static char s_str[64] = {};
                sprintf_s(s_str, "Failure with HRESULT of %08X",
                    static_cast<unsigned int>(result));
                return pszD;
            }

        private:
            HRESULT result;
        };

        // Helper utility converts D3D API failures into exceptions.
        inline void ThrowIfFailed(HRESULT hr)
        {
            if (FAILED(hr))
            {
                throw com_exception(hr);
            }
        }

    public:
        Direct3D11(HWND hWnd, uint32_t width, uint32_t height);
        ~Direct3D11() = default;

        void BeginFrame();
        void EndFrame();
    private:
        Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
        Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
    };

    wchar_t* convertCharArrayToLPCWSTR(const char* charArray);
}