#pragma once
class CStat
{
public:
	CStat();
	~CStat();
public:
	float		Get_Atk() { return m_fAtk; }
	float		Get_Hp() { return m_fHp; }
	float		Get_MaxHp() { return m_fMaxHp; }
public:
	void		Set_Atk(float _fAtk) { m_fAtk = _fAtk; }
	void		Set_Hp(float _fHp) { m_fHp = _fHp; }
	void		Set_MaxHp(float _fMaxHp) { m_fMaxHp = _fMaxHp; }
	void		Damaged(float _fAtk) { m_fHp -= _fAtk; }
private:
	float		m_fAtk;
	float		m_fMaxHp;
	float		m_fHp;
};

