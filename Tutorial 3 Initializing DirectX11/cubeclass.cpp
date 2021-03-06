//////////////////////////
//Filename: modelclass.cpp
//////////////////////////
#include "cubeclass.h"

CubeClass::CubeClass(){
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Position = D3DXVECTOR3(0, 0, 0);
	m_Rotation = D3DXVECTOR3(0, 0, 0);
	m_Scale = D3DXVECTOR3(0, 0, 0);
}

CubeClass::CubeClass(const CubeClass& other){
}

CubeClass::~CubeClass(){
}

bool CubeClass::Initialize(ID3D11Device* device){

	bool result;

	//Initialize the vertex and index buffer that hold the geometry for the triangle
	result = InitializeBuffers(device);
	if (!result)
		return false;

	return true;
}

bool CubeClass::Initialize(ID3D11Device* device, WCHAR* textureFilename, float u1, float v1)
{
	bool result;

	v = v1;
	u = u1;

	// Initialize the vertex and index buffer that hold the geometry for the triangle.
	result = InitializeBuffers(device);
	if (!result)
		return false;

	// Load the texture for this model.
	result = LoadTexture(device, textureFilename);
	if (!result)
		return false;

	return true;
}

void CubeClass::Shutdown(){

	//Release the vertex and index buffers;
	ShutdownBuffers();

	return;
}

void CubeClass::Render(ID3D11DeviceContext* deviceContext){

	//Put the vertex and index buffers on the graphics pipeline to prepare them for drawing
	RenderBuffers(deviceContext);

	return;
}

int CubeClass::GetIndexCount(){

	return m_indexCount;
}

ID3D11ShaderResourceView* CubeClass::GetTexture(){
	return m_Texture->GetTexture();
}

bool CubeClass::InitializeBuffers(ID3D11Device* device){

	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	//Set the number of vertices in the vertex array
	m_vertexCount = 24;

	//Set the number of indices in the index array
	m_indexCount = 36;

	//Create the vertex array
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
		return false;

	//Create the index array
	indices = new unsigned long[m_indexCount];
	if (!indices)
		return false;
	// Front
	vertices[0].position = D3DXVECTOR3(-1, -1, -1);
	vertices[1].position = D3DXVECTOR3(-1, 1, -1);
	vertices[2].position = D3DXVECTOR3(1, -1, -1);
	vertices[3].position = D3DXVECTOR3(1, 1, -1);
	vertices[0].texture = D3DXVECTOR2(0,0);
	vertices[1].texture = D3DXVECTOR2(0,v);
	vertices[2].texture = D3DXVECTOR2(u,0);
	vertices[3].texture = D3DXVECTOR2(u,v);
	vertices[0].normal = D3DXVECTOR3(0, 0, -1);
	vertices[1].normal = D3DXVECTOR3(0, 0, -1);
	vertices[2].normal = D3DXVECTOR3(0, 0, -1);
	vertices[3].normal = D3DXVECTOR3(0, 0, -1);
	// Right
	vertices[4].position = D3DXVECTOR3(1, -1, -1);
	vertices[5].position = D3DXVECTOR3(1, 1, -1);
	vertices[6].position = D3DXVECTOR3(1, -1, 1);
	vertices[7].position = D3DXVECTOR3(1, 1, 1);
	vertices[4].texture = D3DXVECTOR2(0, 0);
	vertices[5].texture = D3DXVECTOR2(0, v);
	vertices[6].texture = D3DXVECTOR2(u, 0);
	vertices[7].texture = D3DXVECTOR2(u, v);
	vertices[4].normal = D3DXVECTOR3 (1, 0, 0);
	vertices[5].normal = D3DXVECTOR3 (1, 0, 0);
	vertices[6].normal = D3DXVECTOR3 (1, 0, 0);
	vertices[7].normal = D3DXVECTOR3 (1, 0, 0);
	// Bottom
	vertices[8].position = D3DXVECTOR3(-1, -1, 1);
	vertices[9].position = D3DXVECTOR3(-1, -1, -1);
	vertices[10].position = D3DXVECTOR3(1, -1, 1);
	vertices[11].position = D3DXVECTOR3(1, -1, -1);
	vertices[8].texture = D3DXVECTOR2(0, 0);
	vertices[9].texture = D3DXVECTOR2(0, v);
	vertices[10].texture = D3DXVECTOR2(u, 0);
	vertices[11].texture = D3DXVECTOR2(u, v);
	vertices[9].normal = D3DXVECTOR3(0, -1, 0);
	vertices[8].normal = D3DXVECTOR3(0, -1, 0);
	vertices[10].normal = D3DXVECTOR3(0, -1, 0);
	vertices[11].normal = D3DXVECTOR3(0, -1, 0);
	// Rear
	vertices[12].position = D3DXVECTOR3(1, -1, 1);
	vertices[13].position = D3DXVECTOR3(1, 1, 1);
	vertices[14].position = D3DXVECTOR3(-1, -1, 1);
	vertices[15].position = D3DXVECTOR3(-1, 1, 1);
	vertices[12].texture = D3DXVECTOR2(0, 0);
	vertices[13].texture = D3DXVECTOR2(0, v);
	vertices[14].texture = D3DXVECTOR2(u, 0);
	vertices[15].texture = D3DXVECTOR2(u, v);
	vertices[12].normal = D3DXVECTOR3(0, 0, 1);
	vertices[13].normal = D3DXVECTOR3(0, 0, 1);
	vertices[14].normal = D3DXVECTOR3(0, 0, 1);
	vertices[15].normal = D3DXVECTOR3(0, 0, 1);
	// Left
	vertices[16].position = D3DXVECTOR3(-1, -1, 1);
	vertices[17].position = D3DXVECTOR3(-1, 1, 1);
	vertices[18].position = D3DXVECTOR3(-1, -1, -1);
	vertices[19].position = D3DXVECTOR3(-1, 1, -1);
	vertices[16].texture = D3DXVECTOR2(0, 0);
	vertices[17].texture = D3DXVECTOR2(0, v);
	vertices[18].texture = D3DXVECTOR2(u, 0);
	vertices[19].texture = D3DXVECTOR2(u, v);
	vertices[16].normal = D3DXVECTOR3(-1, 0, 0);
	vertices[17].normal = D3DXVECTOR3(-1, 0, 0);
	vertices[18].normal = D3DXVECTOR3(-1, 0, 0);
	vertices[19].normal = D3DXVECTOR3(-1, 0, 0);
	//Top
	vertices[20].position = D3DXVECTOR3(-1, 1, -1);
	vertices[21].position = D3DXVECTOR3(-1, 1, 1);
	vertices[22].position = D3DXVECTOR3(1, 1, -1);
	vertices[23].position = D3DXVECTOR3(1, 1, 1);
	vertices[20].texture = D3DXVECTOR2(0, 0);
	vertices[21].texture = D3DXVECTOR2(0, v);
	vertices[22].texture = D3DXVECTOR2(u, 0);
	vertices[23].texture = D3DXVECTOR2(u, v);
	vertices[20].normal = D3DXVECTOR3(0, 1, 0);
	vertices[21].normal = D3DXVECTOR3(0, 1, 0);
	vertices[22].normal = D3DXVECTOR3(0, 1, 0);
	vertices[23].normal = D3DXVECTOR3(0, 1, 0);

	//Front
	indices[0] = 0; 
	indices[1] = 2; 
	indices[2] = 1; 
	indices[3] = 2; 
	indices[4] = 3; 
	indices[5] = 1; 

	//Right
	indices[6] = 4;
	indices[7] = 6;
	indices[8] = 5;
	indices[9] = 6;
	indices[10] = 7;
	indices[11] = 5;

	//Bottom
	indices[12] = 8;
	indices[13] = 10;
	indices[14] = 9;
	indices[15] = 10;
	indices[16] = 11;
	indices[17] = 9;

	//Rear
	indices[18] = 12;
	indices[19] = 14;
	indices[20] = 13;
	indices[21] = 14;
	indices[22] = 15;
	indices[23] = 13;

	//Left
	indices[24] = 17;
	indices[25] = 16;
	indices[26] = 19;
	indices[27] = 16;
	indices[28] = 18;
	indices[29] = 19;

	//Top
	indices[30] = 20;
	indices[31] = 21;
	indices[32] = 23;
	indices[33] = 23;
	indices[34] = 24;
	indices[35] = 20;
	//Set up the description of the static vertex buffer
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType)* m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	//Give the subresource structure a pointer to the vertex data
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	//Now create the vertex buffer
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
		return false;

	//Set up the description of the static index buffer
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long)* m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	//Give the subresource structure a pointer to the index data
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	//Create the index buffer
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
		return false;

	//Release the arrays now that the vertex and index buffers have been created and loaded
	delete[]vertices;
	vertices = 0;

	delete[]indices;
	indices = 0;

	return true;

}

void CubeClass::ShutdownBuffers(){

	//Release the index buffer
	if (m_indexBuffer){
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	//Release the vertex buffer
	if (m_vertexBuffer){
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

void CubeClass::RenderBuffers(ID3D11DeviceContext* deviceContext){

	unsigned int stride;
	unsigned int offset;

	//Set vertex buffer stride and offset
	stride = sizeof(VertexType);
	offset = 0;

	//Set the vertex buffer to active in the input assembler so it can be rendered
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	//Set the index buffer to active in th input assembler so it can be rendered
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//Set the tupe of primitive that should be rendered from this vertex buffer, in this case triangles
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

bool CubeClass::LoadTexture(ID3D11Device* device, WCHAR* filename){

	bool result;

	//Create the texture object
	m_Texture = new TextureClass;
	if (!m_Texture)
		return false;

	//Initialize the texture object
	result = m_Texture->Initialize(device, filename);
	if (!result)
		return false;

	return true;
}

void CubeClass::ReleaseTexture(){

	if (m_Texture){
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}

void CubeClass::SetPosition(D3DXVECTOR3 position){
	m_Position = position;
}
void CubeClass::SetRotation(D3DXVECTOR3 rotation){
	m_Rotation = rotation;
}
void CubeClass::SetScale(D3DXVECTOR3 scale){
	m_Scale = scale;
}
D3DXVECTOR3 CubeClass::GetPosition(){
	return m_Position;
}
D3DXVECTOR3 CubeClass::GetRotation(){
	return m_Rotation;
}
D3DXVECTOR3 CubeClass::GetScale(){
	return m_Scale;
}
D3DXMATRIX CubeClass::GetMatrix(){
	D3DXMATRIX FinalM, TranslationM, RotationxM, RotationyM, RotationzM, ScaleM;
	D3DXMatrixIdentity(&FinalM);
	D3DXMatrixTranslation(&TranslationM, m_Position.x, m_Position.y, m_Position.z);
	D3DXMatrixRotationX(&RotationxM, D3DXToDegree(m_Rotation.x));
	D3DXMatrixRotationY(&RotationyM, D3DXToDegree(m_Rotation.y));
	D3DXMatrixRotationZ(&RotationzM, D3DXToDegree(m_Rotation.z));
	D3DXMatrixScaling(&ScaleM, m_Scale.x, m_Scale.y, m_Scale.z);
	FinalM = FinalM  * ScaleM * RotationxM * RotationyM * RotationzM * TranslationM;
	return FinalM;
}