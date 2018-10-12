/**
 * 用户密码及权限数据
**/
#ifndef DATA_USER_H
#define DATA_USER_H

#include "../../common/common.h"

#define NUMERIC_SUPPORT	
#define FINGER_PRINT_SUPPORT
#define CARD_SUPPORT
#define FACE_SUPPORT
#define PALM_PRINT_SUPPORT
#define LRIS_SUPPORT
#define BLUETOOTH_SUPPORT

#define PHOTO_SUPPORT

#define NULL 0

/*
 * 密码类型
*/
typedef enum {
#ifdef NUMERIC_SUPPORT
	NUMERIC 						,//数字密码
#endif
#ifdef FINGER_PRINT_SUPPORT
	FINGER_PRINT 					,//指纹密码
#endif
#ifdef CARD_SUPPORT
	CARD 							,//门禁卡
#endif
#ifdef FACE_SUPPORT
	FACE 							,//人脸
#endif
#ifdef PALM_PRINT_SUPPORT
	PALM_PRINT 						,//掌纹
#endif
#ifdef LRIS_SUPPORT
	LRIS 							,//虹膜
#endif
#ifdef BLUETOOTH_SUPPORT	
	BLUETOOTH 						,//蓝牙
#endif
	
	PWD_TYPE_MAX					//最大密码类型
}PWD_TYPE, *PPWD_TYPE;

/*
 * 权限类型
 */
typedef enum{
	FORBID 							= 0,//禁用
	ADMIN 							= 1,//管理员
	GUEST 							= 2,//访客
	
} PERMISSION, *PPERMISSION;

/*
 * 数据缓冲
 */
typedef struct _BUFFER{
	U16 len;
	void* buffer;
	
	struct{
		bool (*is)(struct _BUFFER* p, struct _BUFFER* n);
	} ops;
} BUFFER, *PBUFFER;

PBUFFER init_buffer(PBUFFER buf, U16 len, void* data);


/*
 *密码数据 
 */
typedef struct _PWD{
	PWD_TYPE type;
	BUFFER buffer;
	
	struct{
		bool (*is)(struct _PWD* p, struct _PWD* n);
	} ops;
} PWD, *PPWD;

PPWD init_pwd(PPWD pwd, PWD_TYPE type, PBUFFER buffer);

/*
 * 用户数据
 */
typedef struct _USER{
	//用户索引
	U16 index;
	//用户权限
	PERMISSION permission;
	
#ifdef PHOTO_SUPPORT
	//用户照片
	char* photo;
#endif

	//密码组，支持每个类型密码各一个
	PWD pwds[PWD_TYPE_MAX];
	
	//操作接口
	struct{
		/*
		 * 判断是否相同
		 */
		bool (*is)(struct _USER* u, struct _USER* n);
		
		/*
		 * 设置密码
		 */
		int (*set_pwd)(struct _USER* u, PPWD pwd);
		
		/*
		 * 删除密码
		 */
		int (*remove_pwd)(struct _USER* u, PPWD pwd);
		
		/*
		 * 判断用户是否拥有密码
		 */
		bool (*is_owner)(struct _USER* u, PPWD pwd);
		
		/*
		 * 判断是否有权限
		 */
		bool (*is_access)(struct _USER* u, PERMISSION p);
	}ops;
	
} USER, *PUSER;

/*
 * 创建用户
 */
PUSER init_user(PUSER u, U16 index, PERMISSION permission);


/*
 * 插入新用户
 */
int insert_user(PUSER pUser);

/*
 * 删除用户
 */
int remove_user(PUSER pUser);

/*
 * 判断用户是否存在
 */
bool is_user_exist(PUSER pUser);

/*
 * 统计用户个数
 */
 int get_user_count();
 
 
 /*
  * 根据密码查找用户
  */ 
 PUSER find_user_by_pwd(PPWD pPwd);
 /*
  * 根据用户索引查找用户
  */
 PUSER find_user_by_index(U16 index);
 
#endif