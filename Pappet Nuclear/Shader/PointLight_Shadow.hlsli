////�X�L�j���O���b�V���ł̃|�C���g���C�g���g�����e
////���_�V�F�[�_�̓���
//struct VS_INPUT
//{
//	float4 Position          : POSITION ;               //���W(���[�J�����W)
//	int4 BlendIndices0       : BLENDINDICES0 ;          //�X�L�j���O�����p Float�^�萔�z��C���f�b�N�X
//	float4 BlendWeight0      : BLENDWEIGHT0 ;           //�X�L�j���O�����p�E�G�C�g�l
//	float3 Normal            : NORMAL0 ;                //�@��(���[�J�����W)
//	float4 Diffuse           : COLOR0 ;                 //�f�B�t���[�Y�J���[
//	float4 Specular          : COLOR1 ;                 //�X�y�L�����J���[
//	float4 TexCoords0        : TEXCOORD0 ;              //�e�N�X�`�����W
//};
//
////���_�V�F�[�_�̏o��
//struct VS_OUTPUT
//{
//	float4 Position          : POSITION ;               //���W(�ˉe���)
//	float4 Diffuse           : COLOR0 ;                 //�f�B�t���[�Y�J���[
//	float4 Specular          : COLOR1 ;                 //�X�y�L�����J���[
//	float2 TexCoords0        : TEXCOORD0 ;              //�e�N�X�`�����W
//	float4 DPPosition0       : TEXCOORD1 ;              //�[�x�o�b�t�@0�����_�����O���̍��W(�ˉe���)
//	float4 DPPosition1       : TEXCOORD2 ;              //�[�x�o�b�t�@1�����_�����O���̍��W(�ˉe���)
//	float4 DPPosition2       : TEXCOORD3 ;              //�[�x�o�b�t�@2�����_�����O���̍��W(�ˉe���)
//	float4 DPPosition3       : TEXCOORD4 ;              //�[�x�o�b�t�@3�����_�����O���̍��W(�ˉe���)
//	float4 DPPosition4       : TEXCOORD5 ;              //�[�x�o�b�t�@4�����_�����O���̍��W(�ˉe���)
//	float4 DPPosition5       : TEXCOORD6 ;              //�[�x�o�b�t�@5�����_�����O���̍��W(�ˉe���)
//};
//
////�}�e���A���p�����[�^
//struct VS_CONST_MATERIAL
//{
//	float4 Diffuse ;                                    //�}�e���A���f�B�t���[�Y�J���[
//	float4 Specular ;                                   //�}�e���A���X�y�L�����J���[
//	float4 Power ;                                      //�}�e���A���X�y�L�����n�C���C�g�̋���
//};
//
////���C�g�p�����[�^
//struct VS_CONST_LIGHT
//{
//	float4 Position ;                                   //���W(�r���[���)
//	float3 Direction ;                                  //����(�r���[���)
//	float4 Diffuse ;                                    //�f�B�t���[�Y�J���[
//	float4 Specular ;                                   //�X�y�L�����J���[
//	float4 Ambient ;                                    //�A���r�G���g�J���[�ƃ}�e���A���̃A���r�G���g�J���[����Z��������
//	float4 Range_FallOff_ATO_AT1 ;                      //x:�L������ y:�X�|�b�g���C�g�pFallOff z:�����ɂ�錸�������p�p�����[�^0 w:�����ɂ�錸�������p�p�����[�^1
//	float4 AT2_SpotP0_SpotP1 ;                          //x:�����ɂ�錸�������p�p�����[�^2 y:�X�|�b�g���C�g�p�p�����[�^0(cos(Phi / 2.0f)) z:�X�|�b�g���C�g�p�p�����[�^1(1.0f / (cos(Theta / 2.0f) - cos(Phi / 2.0f)))
//};
//
////C++���Őݒ肷��萔�̒�`
//float4             cfAmbient_Emissive       : register(c1) ;                //�}�e���A���G�~�b�V�u�J���[ + �}�e���A���A���r�G���g�J���[ * �O���[�o���A���r�G���g�J���[
//float4             cfProjectionMatrix[4]    : register(c2) ;                //�r���[   �@���@�@�ˉe���
//float4             cfViewMatrix[3]          : register(c6) ;                //���[���h �@���@�@�r���[�s��
//float4             cfLocalWorldMatrix[162]  : register(c94) ;               //���[�J���@ ��    ���[���h�s��
//VS_CONST_MATERIAL  cfMaterial               : register(c11) ;               //�}�e���A���p�����[�^
//VS_CONST_LIGHT     cfLight                  : register(c14) ;               //�L�����C�g�O�Ԃ̃p�����[�^
//
//matrix             cfDepthViewMatrix0       : register(c43) ;               //�[�x�o�b�t�@0�̃����_�����O���̃��[���h    ���@�@�r���[�s��
//matrix             cfDepthProjectionMatrix0 : register(c47) ;               //�[�x�o�b�t�@0�̃����_�����O���̃r���[�@�@�@���@�@�ˉe�s��
//matrix             cfDepthViewMatrix1       : register(c51) ;               //�[�x�o�b�t�@1�̃����_�����O���̃��[���h�@�@���@�@�r���[�s��
//matrix             cfDepthProjectionMatrix1 : register(c55) ;               //�[�x�o�b�t�@1�̃����_�����O���̃r���[�@�@�@���@�@�ˉe�s��
//matrix             cfDepthViewMatrix2       : register(c59) ;               //�[�x�o�b�t�@2�̃����_�����O���̃��[���h�@�@���@�@�r���[�s��
//matrix             cfDepthProjectionMatrix2 : register(c63) ;               //�[�x�o�b�t�@2�̃����_�����O���̃r���[�@�@�@���@�@�ˉe�s��
//matrix             cfDepthViewMatrix3       : register(c67) ;               //�[�x�o�b�t�@3�̃����_�����O���̃��[���h�@�@���@�@�r���[�s��
//matrix             cfDepthProjectionMatrix3 : register(c71) ;               //�[�x�o�b�t�@3�̃����_�����O���̃r���[�@�@�@���@�@�ˉe�s��
//matrix             cfDepthViewMatrix4       : register(c75) ;               //�[�x�o�b�t�@4�̃����_�����O���̃��[���h�@�@���@�@�r���[�s��
//matrix             cfDepthProjectionMatrix4 : register(c79) ;               //�[�x�o�b�t�@4�̃����_�����O���̃r���[�@�@�@���@�@�ˉe�s��
//matrix             cfDepthViewMatrix5       : register(c83) ;               //�[�x�o�b�t�@5�̃����_�����O���̃��[���h�@�@���@�@�r���[�s��
//matrix             cfDepthProjectionMatrix5 : register(c87) ;               //�[�x�o�b�t�@5�̃����_�����O���̃r���[�@�@�@���@�@�ˉe�s��
//
////main�֐�
//VS_OUTPUT main(VS_INPUT VSInput)
//{
//	VS_OUTPUT VSOutput;
//	float4 lWorldPosition;
//	float4 lViewPosition;
//	float4 lDViewPsosition;
//	float3 lWorld
//}