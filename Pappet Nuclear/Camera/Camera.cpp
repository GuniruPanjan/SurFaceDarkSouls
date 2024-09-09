#include "Camera.h"
#include "Map/Map.h"
//�x�����W�A���ɕϊ�
#define D2R(deg) ((deg)*DX_PI_F/180.0f)

namespace
{
	//�G�ƃv���C���[�̍��W�̍������߂�
	VECTOR dif[ENEMY_NOW];
	float difSize[ENEMY_NOW];
}


Camera::Camera():
	m_cameraAngle(VGet(0.0f,0.0f,0.0f)),
	m_cameraPos(VGet(0.0f,0.0f,0.0f)),
	m_cameraTarget(VGet(0.0f,0.0f,0.0f)),
	input(),
	m_radius(0.0f),
	m_HitFlag(false),
	m_WallNum(0),
	m_FloorNum(0),
	m_HitDimNum(0)
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetUseBackCulling(true);

	m_radius = 3.0f;

	//��ƂȂ�J�����̍��W
	m_cameraPos = VGet(0.0f, 50.0f, 100.0f);

	//�J�����̃^�[�Q�b�g���W������
	m_cameraTarget = VGet(0.0f, 5.0f, 0.0f);

	//�J�����̃A���O�������ݒ�
	m_cameraAngle = VGet(D2R(-20.0f), 97.4f, 0.0f);

	SetCameraNearFar(0.1f, 1000.0f);
}

void Camera::Update(Player& player)
{
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	//�G�����b�N�I�����ĂȂ��Ƃ�
	if (player.GetLock() == false)
	{
		//���L�[
		if (input.Rx < 0)
		{
			m_cameraAngle.y -= D2R(1.0f);
			
		}
		//�E�L�[
		if (input.Rx > 0)
		{
			m_cameraAngle.y += D2R(1.0f);
			
		}
		//��L�[
		if (input.Ry < 0)
		{
			//�J�������v���C���[�𒴂��Ȃ����炢�܂�
			if (m_cameraAngle.x <= 0.7f)
			{
				m_cameraAngle.x += D2R(1.0f);
			}

		}
		//���L�[
		if (input.Ry > 0)
		{
			//�J�������n�ʂɂ߂肱�܂Ȃ��悤��
			if (m_cameraPos.y >= 15.2f + player.GetPosY())
			{
				m_cameraAngle.x -= D2R(1.0f);
			}

		}

		//��̃x�N�g��
		VECTOR Direction = VGet(0.0f, 100.0f, -100.0f);

		//X����]�s��
		MATRIX matrixX = MGetRotX(m_cameraAngle.x);
		//Y����]�s��
		MATRIX matrixY = MGetRotY(m_cameraAngle.y);

		//�s��̍���
		MATRIX matrix = MMult(matrixX, matrixY);

		//��x�N�g�����s��ŕϊ�
		Direction = VTransform(Direction, matrix);

		//�J�������W�̓v���C���[���W���班���͂Ȃꂽ�Ƃ���
		m_cameraPos = VAdd(player.GetPos(), Direction);

		//�����_�̍��W�̓v���C���[���W�̏�����
		m_cameraTarget = VAdd(player.GetPos(), VGet(0.0f, 50.0f, 0.0f));
	}

	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_cameraTarget);
}

void Camera::LockUpdate(Player& player, Enemy& enemy, int max)
{
	//�G�̋������v���C���[�ɋ߂�������b�N����悤�ɂ���
	dif[0] = VSub(enemy.GetPos(0), player.GetPos());
	dif[1] = VSub(enemy.GetPos(1), player.GetPos());
	dif[2] = VSub(enemy.GetPos(2), player.GetPos());
	dif[3] = VSub(enemy.GetPos(3), player.GetPos());
	dif[4] = VSub(enemy.GetPos(4), player.GetPos());

	difSize[0] = VSize(dif[0]);
	difSize[1] = VSize(dif[1]);
	difSize[2] = VSize(dif[2]);
	difSize[3] = VSize(dif[3]);
	difSize[4] = VSize(dif[4]);


	//���b�N�I�������Ƃ�
	if (player.GetLock() == true)
	{
		//�{�X��̎��̃J����
		if (enemy.GetBattale() == true)
		{
			//�����_�͓G�̍��W�ɂ���
			m_cameraTarget = VAdd(enemy.GetBossPos(), VGet(0.0f, 20.0f, 0.0f));

			//�v���C���[�ƃG�l�~�[��X���W�̍������߂�
			float X = enemy.GetBossPosX() - player.GetPosX();

			//�v���C���[�ƃG�l�~�[��Z���W�̍������߂�
			float Z = enemy.GetBossPosZ() - player.GetPosZ();

			//�p�x���o��
			float angle = atan2f(X, Z);

			m_x = X;
			m_z = Z;

			//�G����v���C���[�ɐL�т��̃x�N�g�������߂�
			VECTOR pos = VSub(player.GetPos(), enemy.GetBossPos());

			//�x�N�g���̐��K��
			VECTOR posTarget = VNorm(pos);

			posTarget.x *= 130.0f;
			posTarget.z *= 130.0f;

			//�J�������ǂꂾ���v���C���[�̍��W��荂������ݒ�
			posTarget.y = 80.0f;

			m_cameraAngle.y = angle;

			//�v���C���[�̍��W�ɋ��߂��x�N�g���𑫂��āA�J�����̍��W�Ƃ���
			m_cameraPos = VAdd(player.GetPos(), posTarget);
		}
		//�{�X��ȊO�̃^�[�Q�b�g
		if (enemy.GetBattale() == false)
		{
			//��Ԗڂ̓G���^�[�Q�b�g
			if (difSize[0] < difSize[1] && difSize[0] < difSize[2] && difSize[0] < difSize[3] &&
				difSize[0] < difSize[4])
			{
				WeakLockUpdate(player, enemy, 0);
			}
			//2�Ԗڂ̓G���^�[�Q�b�g
			if (difSize[1] < difSize[0] && difSize[1] < difSize[2] && difSize[1] < difSize[3] &&
				difSize[1] < difSize[4])
			{
				WeakLockUpdate(player, enemy, 1);
			}
			//3�Ԗڂ̓G���^�[�Q�b�g
			if (difSize[2] < difSize[1] && difSize[2] < difSize[0] && difSize[2] < difSize[3] &&
				difSize[2] < difSize[4])
			{
				WeakLockUpdate(player, enemy, 2);
			}
			//4�Ԗڂ̓G���^�[�Q�b�g
			if (difSize[3] < difSize[1] && difSize[3] < difSize[2] && difSize[3] < difSize[0] &&
				difSize[3] < difSize[4])
			{
				WeakLockUpdate(player, enemy, 3);
			}
			//5�Ԗڂ̓G���^�[�Q�b�g
			if (difSize[4] < difSize[1] && difSize[4] < difSize[2] && difSize[4] < difSize[3] &&
				difSize[4] < difSize[0])
			{
				WeakLockUpdate(player, enemy, 4);
			}

			////�����_�͓G�̍��W�ɂ���
			//m_cameraTarget = VAdd(enemy.GetPos(max), VGet(0.0f, 20.0f, 0.0f));

			////�v���C���[�ƃG�l�~�[��X���W�̍������߂�
			//float X = enemy.GetPosX(max) - player.GetPosX();

			////�v���C���[�ƃG�l�~�[��Z���W�̍������߂�
			//float Z = enemy.GetPosZ(max) - player.GetPosZ();

			////�p�x���o��
			//float angle = atan2f(X, Z);

			//m_x = X;
			//m_z = Z;

			////�G����v���C���[�ɐL�т��̃x�N�g�������߂�
			//VECTOR pos = VSub(player.GetPos(), enemy.GetPos(max));

			////�x�N�g���̐��K��
			//VECTOR posTarget = VNorm(pos);

			//posTarget.x *= 130.0f;
			//posTarget.z *= 130.0f;

			////�J�������ǂꂾ���v���C���[�̍��W��荂������ݒ�
			//posTarget.y = 80.0f;

			//m_cameraAngle.y = angle;

			////�v���C���[�̍��W�ɋ��߂��x�N�g���𑫂��āA�J�����̍��W�Ƃ���
			//m_cameraPos = VAdd(player.GetPos(), posTarget);
		}

	}
}

void Camera::WeakLockUpdate(Player& player, Enemy& enemy, int weak)
{
	//�����_�͓G�̍��W�ɂ���
	m_cameraTarget = VAdd(enemy.GetPos(weak), VGet(0.0f, 20.0f, 0.0f));

	//�v���C���[�ƃG�l�~�[��X���W�̍������߂�
	float X = enemy.GetPosX(weak) - player.GetPosX();

	//�v���C���[�ƃG�l�~�[��Z���W�̍������߂�
	float Z = enemy.GetPosZ(weak) - player.GetPosZ();

	//�p�x���o��
	float angle = atan2f(X, Z);

	m_x = X;
	m_z = Z;

	//�G����v���C���[�ɐL�т��̃x�N�g�������߂�
	VECTOR pos = VSub(player.GetPos(), enemy.GetPos(weak));

	//�x�N�g���̐��K��
	VECTOR posTarget = VNorm(pos);

	posTarget.x *= 130.0f;
	posTarget.z *= 130.0f;

	//�J�������ǂꂾ���v���C���[�̍��W��荂������ݒ�
	posTarget.y = 80.0f;

	m_cameraAngle.y = angle;

	//�v���C���[�̍��W�ɋ��߂��x�N�g���𑫂��āA�J�����̍��W�Ƃ���
	m_cameraPos = VAdd(player.GetPos(), posTarget);
}

void Camera::HitObj(Map& map)
{
	int j;

	//�v���C���[�̍��W����J�����̕����x�N�g�����v�Z����
	auto playerToCamera = VSub(m_cameraPos, m_cameraTarget);

	//�����Ƒ傫���ɕ�����
	auto vec = VNorm(playerToCamera);
	auto length = VSize(playerToCamera);

	//�v���C���[�̎��͂ɂ���R���W�����̃|���S�����擾����
	HitDim = MV1CollCheck_Sphere(map.GetCollisionMap(), -1, map.GetVectorMapPos(), 1500.0f);

	//���o�����v���C���[�̎��͂̃|���S�������������
	MV1CollResultPolyDimTerminate(HitDim);

	//���o���ꂽ�|���S�����ǃ|���S��(XZ���ʂɐ����ȃ|���S��)�����|���S��(XZ���ʂɐ����ł͂Ȃ��|���S��)���𔻒f����
	for (int i = 0; i < HitDim.HitNum; i++)
	{
		//XZ���ʂɐ������ǂ����̓|���S���̖@����Y������0�Ɍ���Ȃ��߂����ǂ����Ŕ��f����
		if (HitDim.Dim[i].Normal.y < 0.000001f && HitDim.Dim[i].Normal.y > -0.0000001f)
		{

			if (HitDim.Dim[i].Position[0].y > m_cameraPos.y + 1.0f ||
				HitDim.Dim[i].Position[1].y > m_cameraPos.y + 1.0f ||
				HitDim.Dim[i].Position[2].y > m_cameraPos.y + 1.0f)
			{
				//�|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
				if (m_WallNum < PLAYER_MAX_HITCOLL)
				{
					//�|���S���̍\���̂̃A�h���X��ǃ|���S���|�C���^�z��ɕۑ�����
					m_Wall[m_WallNum] = &HitDim.Dim[i];

					//�ǃ|���S���̐������Z����
					m_WallNum++;
				}
			}
		}
	}

	//�ǃ|���S���Ɠ����蔻�菈��
	if (m_WallNum != 0)
	{
		//�ǂɓ����������ǂ����̃t���O�͏�����Ԃł́u�������Ă��Ȃ��v�ɂ��Ă���
		m_HitFlag = false;

		//�ǃ|���S���̐������J��Ԃ�
		for (int i = 0; i < m_WallNum; i++)
		{
			//i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
			m_Poly = m_Wall[i];

			//�|���S���ƃv���C���[���������Ă��Ȃ������玟�̃J�E���g��
			if (HitCheck_Sphere_Triangle(m_cameraPos, m_radius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == false) continue;

			//�����ɂ�����|���S���ƃv���C���[���������Ă���Ƃ������ƂȂ̂ŁA�|���S���ɓ��������t���O�𗧂Ă�
			m_HitFlag = true;

			//�V���Ȉړ����W�ŕǃ|���S���Ɠ������Ă��Ȃ����ǂ����𔻒肷��
			for (j = 0; j < m_WallNum; j++)
			{
				//j�Ԗڂ̕ǃ|���S���Ɠ������Ă��Ȃ����ǂ����𔻒肷��
				m_Poly = m_Wall[j];

				//�������Ă����烋�[�v���甲����
				if (HitCheck_Sphere_Triangle(m_cameraPos, m_radius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == true) break;
			}

			//j��m_WallNum�������ꍇ�͂ǂ̃|���S���Ƃ�������Ȃ������Ƃ������ƂȂ̂�
			//�ǂɓ��������t���O��|���������Ń��[�v���甲����
			if (j == m_WallNum)
			{
				m_HitFlag = false;
				break;
			}

		}

		//�ړ����Ă��Ȃ��ꍇ�̏���

			//�ǃ|���S���̐������J��Ԃ�
		for (int i = 0; i < m_WallNum; i++)
		{
			//i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
			m_Poly = m_Wall[i];

			//�|���S���ɓ������Ă����瓖�������t���O�𗧂Ă���Ń��[�v���甲����
			if (HitCheck_Sphere_Triangle(m_cameraPos, m_radius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == true)
			{
				m_HitFlag = true;
				break;
			}

		}

		//�ǂɓ������Ă�����ǂ��牟���o���������s��
		if (m_HitFlag == true)
		{
			//�ǂ���̉����o�����������݂�ő吔�����J��Ԃ�
			for (int i = 0; i < PLAYER_MAX_HITCOLL; i++)
			{
				//�ǃ|���S���̐������J��Ԃ�
				for (int k = 0; k < m_WallNum; k++)
				{
					//j�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
					m_Poly = m_Wall[k];

					//�v���C���[�Ɠ������Ă��邩����
					if (HitCheck_Sphere_Triangle(m_cameraPos, m_radius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == false) continue;

					//�������Ă�����K�苗�����v���C���[��ǂ̖@�������Ɉړ�������
					//m_cameraPos = VAdd(m_cameraPos, VScale(m_Poly->Normal, 1.0f));
					//�������k�߂�
					length *= 0.998f;

					auto checkPos = VAdd(m_cameraPos, VScale(vec, length));

					m_cameraPos = checkPos;

					//�ړ�������ŕǃ|���S���ƐڐG���Ă��邩�ǂ����𔻒�
					for (j = 0; j < m_WallNum; j++)
					{
						//�������Ă����烋�[�v�𔲂���
						m_Poly = m_Wall[j];
						if (HitCheck_Sphere_Triangle(m_cameraPos, m_radius, m_Poly->Position[0], m_Poly->Position[1], m_Poly->Position[2]) == true) break;

					}

					//���ׂẴ|���S���Ɠ������Ă��Ȃ������烋�[�v�I��
					if (j == m_WallNum) break;
				}

				//i��m_WallNum�ł͂Ȃ��ꍇ�͑S���̃|���S���ŉ����o�������݂�O�ɂ��ׂĂ̕ǃ|���S���ƐڐG���Ȃ��Ȃ����Ƃ������ƂȂ̂Ń��[�v���甲����
				if (i != m_WallNum) break;
			}
		}
	}
}

void Camera::Draw()
{
	//DrawFormatString(0, 240, 0xffffff, "dif1.x : %f,dif1.z : %f", difX[0], difZ[0]);
	//DrawFormatString(0, 260, 0xffffff, "dif2.x : %f,dif2.z : %f", difX[1], difZ[1]);
	//DrawFormatString(0, 280, 0xffffff, "dif3.x : %f,dif3.z : %f", difX[2], difZ[2]);
	//DrawFormatString(0, 300, 0xffffff, "dif4.x : %f,dif4.z : %f", difX[3], difZ[3]);
	//DrawFormatString(0, 320, 0xffffff, "dif5.x : %f,dif5.z : %f", difX[4], difZ[4]);

}

void Camera::End()
{
}
