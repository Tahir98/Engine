#include "Direct3D11.h"

#pragma comment(lib, "d3d11.lib")

DX::Direct3D11::Direct3D11(HWND hWnd, uint32_t width, uint32_t height)
{
	DXGI_SWAP_CHAIN_DESC scd = {};
	scd.BufferDesc.Width = 0;
	scd.BufferDesc.Height = 0;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 0;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = hWnd;
	scd.Windowed = true;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = 0;

	ThrowIfFailed(D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&scd,
		&pSwapChain,
		&pDevice,
		NULL,
		&pContext
	));

	Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;
	ThrowIfFailed(pSwapChain->GetBuffer(0u, __uuidof(ID3D11Resource), &pBackBuffer));
	ThrowIfFailed(pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget));

	pContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), nullptr);

	D3D11_VIEWPORT vp = {};
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	pContext->RSSetViewports(1u, &vp);
}

void DX::Direct3D11::BeginFrame()
{
	float color[] =
	{
		0.5f,
		0.0f,
		0.8f
	};
	pContext->ClearRenderTargetView(pTarget.Get(), color);
}

void DX::Direct3D11::EndFrame()
{
	pSwapChain->Present(1u, 0u);
}

wchar_t* DX::convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}
