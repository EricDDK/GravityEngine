#pragma once
#include "GDxPreInclude.h"
#include "GDxRtv.h"
#include "GDxDescriptorHeap.h"






struct GDxUavProperties
{
	DXGI_FORMAT mUavFormat;

	// RtvWidth = viewportWidth * mWidthPercentage
	float mWidthPercentage = 1;
	float mHeightPercentage = 1;

	FLOAT mClearColor[4] = { 0,0,0,0 };
};

class GDxUav
{
public:

	GDxUav() = delete;
	GDxUav(ID3D12Device* device, UINT ClientWidth, UINT ClientHeight,
		CD3DX12_CPU_DESCRIPTOR_HANDLE cpuSrv,
		CD3DX12_GPU_DESCRIPTOR_HANDLE gpuSrv,
		GDxUavProperties uavProperties,
		bool ScaledByViewport = true,
		bool CreateRtv = false
	);
	GDxUav(const GDxUav& rhs) = delete;
	GDxUav& operator=(const GDxUav& rhs) = delete;
	~GDxUav() = default;

	void BuildResources();

	void BuildDescriptors();

	void OnResize(UINT newWidth, UINT newHeight);

	CD3DX12_GPU_DESCRIPTOR_HANDLE GetGpuSrv();

	CD3DX12_GPU_DESCRIPTOR_HANDLE GetGpuUav();

	D3D12_CPU_DESCRIPTOR_HANDLE GetCpuRtv();

	void SetViewportAndScissorRect(UINT Width, UINT Height);

	UINT GetSize();

	bool ResourceNotNull();

	ID3D12Resource* GetResource();

	DXGI_FORMAT GetFormat();

	D3D12_VIEWPORT mViewport;
	D3D12_RECT mScissorRect;

	GDxUavProperties mProperties;

	GDxDescriptorHeap mRtvHeap;

private:

	ID3D12Device* md3dDevice;

	UINT mClientWidth;
	UINT mClientHeight;

	CD3DX12_CPU_DESCRIPTOR_HANDLE mCpuSrv;
	CD3DX12_GPU_DESCRIPTOR_HANDLE mGpuSrv;

	CD3DX12_CPU_DESCRIPTOR_HANDLE mCpuUav;
	CD3DX12_GPU_DESCRIPTOR_HANDLE mGpuUav;

	UINT SrvUavDescriptorSize;

	bool bScaledByViewport = true;

	Microsoft::WRL::ComPtr<ID3D12Resource> mResource = nullptr;

	bool bCreateRtv = false;

	void SetDescriptorSize();

	std::shared_ptr<GDxRtv> mRtv;

};

