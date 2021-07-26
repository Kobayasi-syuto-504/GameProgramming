#ifndef CMODELX_H   //�C���N���[�h�K�[�h
#define CMODELX_H

#define MODEL_FILE "sample.blend.x"//���̓t�@�C����
//�̈������}�N����
#define SAFE_DELETE_ARRAY(a){if(a)delete[]a;a=0;}
//�z��̃T�C�Y�擾���}�N����
#define ARRAY_SIZE(a)(sizeof(a)/sizeof(a[0]))
#include <vector>
#include "CMatrix.h"
#include"CVector.h"
class CModelX;
class CMaterial;//�N���X�̐錾
/*
CSkinWeights
*/
class CSkinWeights{
public:
	char*mpFrameName;//�t���[����
	int mFrameIndex;//�t���[���ԍ�
	int mIndexNum;//���_�ԍ���
	int *mpIndex;//���_�ԍ��z��
	float*mpWeight;//���_�E�F�C�g�z��
	CMatrix mOffset;//�I�t�Z�b�g�}�g���N�X


	CSkinWeights(CModelX*model);

	~CSkinWeights(){
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpIndex);
		SAFE_DELETE_ARRAY(mpWeight);
	}
};
//CMesh�N���X�̒�`
class CMesh{
public:

	int mVertexNum;   //���_��
	CVector *mpVertex; //���_�f�[�^
	int mFaceNum;//�搔
	int *mpVertexIndex;//����\�����钸�_�ԍ�
	int mNormalNum;  //�@����
	CVector*mpNormal;//�@���f�[�^
	int mMaterialNum;//�}�e���A����
	int mMaterialIndexNum;//�}�e���A���ԍ���
	int*mpMaterialIndex;//�}�e���A���ԍ�
	std::vector<CMaterial*>mMaterial;//�}�e���A���f�[�^
	//�X�L���E�F�C�g
	std::vector<CSkinWeights*>mSkinWeights;

	//�R���X�g���N�^
	CMesh()
		:mVertexNum(0)
		, mpVertex(0)
		, mFaceNum(0)
		, mpVertexIndex(nullptr)
		, mNormalNum(0)
		, mpNormal(nullptr)
		, mMaterialNum(0)
		, mMaterialIndexNum(0)
		, mpMaterialIndex(nullptr)

	{}
	//�f�X�g���N�^
	~CMesh(){
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
		SAFE_DELETE_ARRAY(mpNormal);
		SAFE_DELETE_ARRAY(mpMaterialIndex);
		//�X�L���E�F�C�g�̍폜
		for (int i = 0; i < mSkinWeights.size(); i++){
			delete mSkinWeights[i];
		}
	}
	//�ǂݍ��ݏ���
	void Init(CModelX*model);

	void Render();
	
	
};

//CModelXFrame�N���X�̒�`
class CModelXFrame{
public:
	std::vector<CModelXFrame*>mChild;//�q�t���[���̔z��
	CMatrix mTransformMatrix;  //�ϊ��s��
	char * mpName;
	int mIndex;
	CMesh mMesh;//Mesh�f�[�^
	//�R���X�g���N�^
	CModelXFrame(CModelX*model);
	//�f�X�g���N�^
	~CModelXFrame(){
		//�q�t���[����S�ĉ������
		std::vector<CModelXFrame*>::iterator itr;
		for (itr = mChild.begin(); itr != mChild.end(); itr++){
			delete*itr;
		}
		//���O�̃G���A���������
		SAFE_DELETE_ARRAY(mpName);
	}
	void Render();
};

/*
CAnimationKey
�A�j���[�V�����N���X
*/
class CAnimationKey{
public:
	//����
	float mTime;
	//�s��
	CMatrix mMatrix;
};
/*
CAnimation
�A�j���[�V�����N���X
*/
class CAnimation{
public:
	char*mpFrameName;
	int mFrameIndex;
	int mKeyNum;//�L�[���i���Ԑ��j
	CAnimationKey*mpKey;//�L�[�̔z��

	CAnimation(CModelX*model);

	~CAnimation(){
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpKey);
	}
};

/*
CAnimationSet
�A�j���[�V�����Z�b�g
*/
class CAnimationSet{
public:


	std::vector<CAnimation*>mAnimation;

	//�A�j���[�V�����Z�b�g��
	char*mpName;
	float mTime;//���ݎ���
	float mWeight;//�d��
	float mMaxTime;//�ő厞��

	CAnimationSet(CModelX*model);

	~CAnimationSet(){
		SAFE_DELETE_ARRAY(mpName);
		//�A�j���[�V�����v�f�̍폜
		for (int i = 0; i < mAnimation.size(); i++){
			delete mAnimation[i];
		}
	}
};



/*
CModelX
X�t�@�C���`����3D���f���f�[�^���v���O�����ŔF������
*/

//���������_�f�[�^�̎�
class CModelX{
public:
	char*mpPointer; //�ǂݍ��݈ʒu

	char mToken[1024]; //���o�����P��̗̈�


	std::vector<CModelXFrame*>mFrame;

	//�A�j���[�V�����Z�b�g�̔z��
	std::vector<CAnimationSet*>mAnimationSet;

	//�t���[�����ɊY������t���[���̃A�h���X��Ԃ�
	CModelXFrame*FindFrame(char*name);

	CModelX()
		:mpPointer(0)
	{}
	~CModelX(){
		if (mFrame.size() > 0)
		{
			delete mFrame[0];
		}
		for (int i = 0; i < mAnimationSet.size(); i++){
			delete mAnimationSet[i];
		}
	}
	//�P��̎��o��
	void GetToken();
	//���������_�f�[�^�̎擾
	float GetFloatToken();
	//�t�@�C���ǂݍ���
	void Load(char*file);
	//�m�[�h�̓ǂݔ�΂�
	void SkipNode();
	//�����f�[�^�̎擾
	int GetIntToken();

	void Render();

    void CModelX::AnimateFrame();
};


#endif


