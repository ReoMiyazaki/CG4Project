#pragma once
#include <string>
#include <DirectXMath.h>
#include <vector>
#include <DirectXTex.h>
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <fbxsdk.h>

struct Node
{
	// 名前
	std::string name;
	// ローカルスケール
	DirectX::XMVECTOR scaling = { 1, 1, 1, 0 };
	// ローカル回転角
	DirectX::XMVECTOR rotation = { 0,0,0,0 };
	// ローカル移動
	DirectX::XMVECTOR translation = { 0,0,0,1 };
	// ローカル変換行列
	DirectX::XMMATRIX transform;
	// グローバル変換行列
	DirectX::XMMATRIX globalTransform;
	// 親ノード
	Node* parent = nullptr;
};

class Model
{
private:	// エイリアス
	// Microsoft::WRL::を省略
	template <class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using TexMetadata = DirectX::TexMetadata;
	using ScrachImage = DirectX::ScratchImage;
	// std::を省略
	using string = std::string;
	template <class T>using vector = std::vector<T>;

public:	// 定数
	// ボーンインデックスの最大数
	static const int MAX_BONE_INDICES = 4;

public:	// サブクラス
	// 頂点データ構造体
	struct VertexPosNormalUvSkin
	{
		DirectX::XMFLOAT3 pos;		// xyz座標
		DirectX::XMFLOAT3 normal;	// 法線ベクトル
		DirectX::XMFLOAT2 uv;		// uv座標
		UINT boneIndex[MAX_BONE_INDICES];	// ボーン 番号
		float boneWeight[MAX_BONE_INDICES];	// ボーン 重み
	};
	// ボーン構造体
	struct Bone
	{
		// 名前
		std::string name;
		// 初期姿勢の逆行列
		DirectX::XMMATRIX invInitialPose;
		// クラスター(FBX側のボーン情報)
		FbxCluster* fbxCluster;
		// コンストラクタ
		Bone(const std::string& name)
		{
			this->name = name;
		}
	};

public:
	// フレンドクラス
	friend class FbxLoader;

	// デストラクタ
	~Model();
	void CreateBuffers(ID3D12Device* device);
	// モデルの変形行列
	const XMMATRIX& GetModelTransform() { return meshNode->globalTransform; }
	// 描画
	void Draw(ID3D12GraphicsCommandList* cmdList);
	// getter
	std::vector<Bone>& GetBones() { return bones; }
	// getter
	FbxScene* GetFbxScene() { return fbxScene; }

private:
	// モデル名
	std::string name;
	// ノード名
	std::vector<Node> nodes;
	// メッシュを持つノード
	Node* meshNode = nullptr;
	// 頂点データ配列
	std::vector<VertexPosNormalUvSkin> vertices;
	// 頂点インデックス配列
	std::vector<unsigned short> indices;
	// アンビエント係数
	DirectX::XMFLOAT3 ambient = { 1,1,1 };
	// ディフューズ係数
	DirectX::XMFLOAT3 diffuse = { 1,1,1 };
	// テクスチャメタデータ
	DirectX::TexMetadata metadata = {};
	// スクラッチイメージ
	DirectX::ScratchImage scrachImg = {};
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff = nullptr;
	// インデックスバッファ
	ComPtr<ID3D12Resource> indexBuff = nullptr;
	// テクスチャバッファ
	ComPtr<ID3D12Resource> texbuff = nullptr;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView = {};
	// SRV用デスクリプターヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapSRV = nullptr;
	// ボーン配列
	std::vector<Bone> bones;
	// FBXシーン
	FbxScene* fbxScene = nullptr;
};

