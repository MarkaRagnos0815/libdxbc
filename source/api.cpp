
#include "bc.h"
using namespace DirectX;
using namespace DirectX::PackedVector;

void BcDecodeBC1(ColorVec* pColor, const uint8_t* pBC) {
    DirectX::D3DXDecodeBC1((XMVECTOR*)pColor, pBC);
}
void BcDecodeBC2(ColorVec* pColor, const uint8_t* pBC) {
    DirectX::D3DXDecodeBC2((XMVECTOR*)pColor, pBC);
}
void BcDecodeBC3(ColorVec* pColor, const uint8_t* pBC) {
    DirectX::D3DXDecodeBC3((XMVECTOR*)pColor, pBC);
}
void BcDecodeBC4U(ColorVec* pColor, const uint8_t* pBC) {
    DirectX::D3DXDecodeBC4U((XMVECTOR*)pColor, pBC);
}
void BcDecodeBC4S(ColorVec* pColor, const uint8_t* pBC) {
    DirectX::D3DXDecodeBC4S((XMVECTOR*)pColor, pBC);
}
void BcDecodeBC5U(ColorVec* pColor, const uint8_t* pBC) {
    DirectX::D3DXDecodeBC5U((XMVECTOR*)pColor, pBC);
}
void BcDecodeBC5S(ColorVec* pColor, const uint8_t* pBC) {
    DirectX::D3DXDecodeBC5S((XMVECTOR*)pColor, pBC);
}
void BcDecodeBC6HU(ColorVec* pColor, const uint8_t* pBC) {
    DirectX::D3DXDecodeBC6HU((XMVECTOR*)pColor, pBC);
}
void BcDecodeBC6HS(ColorVec* pColor, const uint8_t* pBC) {
    DirectX::D3DXDecodeBC6HS((XMVECTOR*)pColor, pBC);
}
void BcDecodeBC7(ColorVec* pColor, const uint8_t* pBC) {
    DirectX::D3DXDecodeBC7((XMVECTOR*)pColor, pBC);
}

void BcEncodeBC1(uint8_t* pBC, const ColorVec* pColor, float threshold, uint32_t flags) {
    DirectX::D3DXEncodeBC1(pBC, (XMVECTOR*)pColor, threshold, flags);
}

void BcEncodeBC2(uint8_t* pBC, const ColorVec* pColor, uint32_t flags) {
    DirectX::D3DXEncodeBC2(pBC, (XMVECTOR*)pColor, flags);
}
void BcEncodeBC3(uint8_t* pBC, const ColorVec* pColor, uint32_t flags) {
    DirectX::D3DXEncodeBC3(pBC, (XMVECTOR*)pColor, flags);
}
void BcEncodeBC4U(uint8_t* pBC, const ColorVec* pColor, uint32_t flags) {
    DirectX::D3DXEncodeBC4U(pBC, (XMVECTOR*)pColor, flags);
}
void BcEncodeBC4S(uint8_t* pBC, const ColorVec* pColor, uint32_t flags) {
    DirectX::D3DXEncodeBC4S(pBC, (XMVECTOR*)pColor, flags);
}
void BcEncodeBC5U(uint8_t* pBC, const ColorVec* pColor, uint32_t flags) {
    DirectX::D3DXEncodeBC5U(pBC, (XMVECTOR*)pColor, flags);
}
void BcEncodeBC5S(uint8_t* pBC, const ColorVec* pColor, uint32_t flags) {
    DirectX::D3DXEncodeBC5S(pBC, (XMVECTOR*)pColor, flags);
}
void BcEncodeBC6HU(uint8_t* pBC, const ColorVec* pColor, uint32_t flags) {
    DirectX::D3DXEncodeBC6HU(pBC, (XMVECTOR*)pColor, flags);
}
void BcEncodeBC6HS(uint8_t* pBC, const ColorVec* pColor, uint32_t flags) {
    DirectX::D3DXEncodeBC6HS(pBC, (XMVECTOR*)pColor, flags);
}
void BcEncodeBC7(uint8_t* pBC, const ColorVec* pColor, uint32_t flags) {
    DirectX::D3DXEncodeBC7(pBC, (XMVECTOR*)pColor, flags);
}
