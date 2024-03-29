#pragma once
#include "Sprite.h"

class PostEffect : public Sprite
{
public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PostEffect();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 描画コマンドの実行
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// シーン描画前処理
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// シーン描画後処理
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// パイプライン生成
	/// </summary>
	void CreateGraphicsPipelineState();

private:
	// 画面クリアカラー
	static const float clearColor[4];

private: // メンバ変数
	// テクスチャバッファ
	ComPtr<ID3D12Resource> texBuff[2];
	// SRVデスクリプターヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;
	// 深度バッファ
	ComPtr<ID3D12Resource> depthBuff;
	// RTV用デスクリプターヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	// DSV用デスクリプターヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapDSV;
	// グラフィックスパイプライン
	ComPtr<ID3D12PipelineState> pipelineState;
	// ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootSignature;
};