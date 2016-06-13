#pragma once

#include "cocos2d.h"
using namespace std;
#define SoundMgr SoundManager::getInstance()
class SoundManager
{
public:
	static SoundManager* getInstance() ;

	inline void setSoundOn(bool flag) { m_isSoundOn = flag ;}  ;
	inline bool getSoundOn(){ return m_isSoundOn ; } ;

	inline void setMusicOn(bool flag) { m_isMusicOn = flag ;}  ;
	inline bool getMusicOn(){ return m_isMusicOn ; } ;

	//��Ч
	void playEffect(int uIndex,int type,bool loop = false) ;
    void playEffect(std::string path ,bool loop = false) ;

	void pauseEffect(int uIndex,int type) ;
	void pauseEffect(std::string path) ;
	//����
	void playBackGroundMusic() ; //����
	void pauseBackGroundMusic() ;//��ͣ
	void stopBackGroundMusic() ;//ֹͣ

private:
	std::string getSoundPath(int uIndex,int type) ;

private:
	static SoundManager* m_instance ;
	std::map<std::string,int> m_mapSoundID ;
	bool m_isSoundOn ;//��Ч
	bool m_isMusicOn ;//��������
	
};

