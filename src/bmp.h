#ifndef _MAJIANG_BMP_H_
#define _MAJIANG_BMP_H_

#include "driver.h"
#include "dvb.h"
#include "midware.h"

/* 背景 */
#include "./bmp/Mj_bg.h"

/* 提示信息 */
#include "./bmp/Mj_info_gang.h"
#include "./bmp/Mj_info_gangf.h"
#include "./bmp/Mj_info_guo.h"
#include "./bmp/Mj_info_guof.h"
#include "./bmp/Mj_info_hu.h"
#include "./bmp/Mj_info_huf.h"
#include "./bmp/Mj_info_peng.h"
#include "./bmp/Mj_info_pengf.h"

/* 
*    位置:手牌
*    方向:下 
*    牌型:条
*/
#include "./bmp/Mj_inPd_s1.h"
#include "./bmp/Mj_inPd_s2.h"
#include "./bmp/Mj_inPd_s3.h"
#include "./bmp/Mj_inPd_s4.h"
#include "./bmp/Mj_inPd_s5.h"
#include "./bmp/Mj_inPd_s6.h"
#include "./bmp/Mj_inPd_s7.h"
#include "./bmp/Mj_inPd_s8.h"
#include "./bmp/Mj_inPd_s9.h"

/* 
*    位置:手牌
*    方向:下 
*    牌型:筒
*/
#include "./bmp/Mj_inPd_t1.h"
#include "./bmp/Mj_inPd_t2.h"
#include "./bmp/Mj_inPd_t3.h"
#include "./bmp/Mj_inPd_t4.h"
#include "./bmp/Mj_inPd_t5.h"
#include "./bmp/Mj_inPd_t6.h"
#include "./bmp/Mj_inPd_t7.h"
#include "./bmp/Mj_inPd_t8.h"
#include "./bmp/Mj_inPd_t9.h"

/* 
*    位置:手牌
*    方向:下 
*    牌型:万
*/
#include "./bmp/Mj_inPd_w1.h"
#include "./bmp/Mj_inPd_w2.h"
#include "./bmp/Mj_inPd_w3.h"
#include "./bmp/Mj_inPd_w4.h"
#include "./bmp/Mj_inPd_w5.h"
#include "./bmp/Mj_inPd_w6.h"
#include "./bmp/Mj_inPd_w7.h"
#include "./bmp/Mj_inPd_w8.h"
#include "./bmp/Mj_inPd_w9.h"

/* 
*    位置:手牌，吃碰的牌
*    方向:下 
*    牌型:条
*/
#include "./bmp/Mj_inPdo_s1.h"
#include "./bmp/Mj_inPdo_s2.h"
#include "./bmp/Mj_inPdo_s3.h"
#include "./bmp/Mj_inPdo_s4.h"
#include "./bmp/Mj_inPdo_s5.h"
#include "./bmp/Mj_inPdo_s6.h"
#include "./bmp/Mj_inPdo_s7.h"
#include "./bmp/Mj_inPdo_s8.h"
#include "./bmp/Mj_inPdo_s9.h"

/* 
*    位置:手牌，吃碰的牌
*    方向:下 
*    牌型:筒
*/
#include "./bmp/Mj_inPdo_t1.h"
#include "./bmp/Mj_inPdo_t2.h"
#include "./bmp/Mj_inPdo_t3.h"
#include "./bmp/Mj_inPdo_t4.h"
#include "./bmp/Mj_inPdo_t5.h"
#include "./bmp/Mj_inPdo_t6.h"
#include "./bmp/Mj_inPdo_t7.h"
#include "./bmp/Mj_inPdo_t8.h"
#include "./bmp/Mj_inPdo_t9.h"

/* 
*    位置:手牌，吃碰的牌
*    方向:下 
*    牌型:万
*/
#include "./bmp/Mj_inPdo_w1.h"
#include "./bmp/Mj_inPdo_w2.h"
#include "./bmp/Mj_inPdo_w3.h"
#include "./bmp/Mj_inPdo_w4.h"
#include "./bmp/Mj_inPdo_w5.h"
#include "./bmp/Mj_inPdo_w6.h"
#include "./bmp/Mj_inPdo_w7.h"
#include "./bmp/Mj_inPdo_w8.h"
#include "./bmp/Mj_inPdo_w9.h"

/* 
*    位置:打出的牌
*    方向:下 
*    牌型:条
*/
#include "./bmp/Mj_outHd_s1.h"
#include "./bmp/Mj_outHd_s2.h"
#include "./bmp/Mj_outHd_s3.h"
#include "./bmp/Mj_outHd_s4.h"
#include "./bmp/Mj_outHd_s5.h"
#include "./bmp/Mj_outHd_s6.h"
#include "./bmp/Mj_outHd_s7.h"
#include "./bmp/Mj_outHd_s8.h"
#include "./bmp/Mj_outHd_s9.h"

/* 
*    位置:打出的牌
*    方向:下 
*    牌型:筒
*/
#include "./bmp/Mj_outHd_t1.h"
#include "./bmp/Mj_outHd_t2.h"
#include "./bmp/Mj_outHd_t3.h"
#include "./bmp/Mj_outHd_t4.h"
#include "./bmp/Mj_outHd_t5.h"
#include "./bmp/Mj_outHd_t6.h"
#include "./bmp/Mj_outHd_t7.h"
#include "./bmp/Mj_outHd_t8.h"
#include "./bmp/Mj_outHd_t9.h"

/* 
*    位置:打出的牌
*    方向:下 
*    牌型:万
*/
#include "./bmp/Mj_outHd_w1.h"
#include "./bmp/Mj_outHd_w2.h"
#include "./bmp/Mj_outHd_w3.h"
#include "./bmp/Mj_outHd_w4.h"
#include "./bmp/Mj_outHd_w5.h"
#include "./bmp/Mj_outHd_w6.h"
#include "./bmp/Mj_outHd_w7.h"
#include "./bmp/Mj_outHd_w8.h"
#include "./bmp/Mj_outHd_w9.h"

/* 
*    位置:打出的牌
*    方向:左
*    牌型:条
*/
#include "./bmp/Mj_outHl_s1.h"
#include "./bmp/Mj_outHl_s2.h"
#include "./bmp/Mj_outHl_s3.h"
#include "./bmp/Mj_outHl_s4.h"
#include "./bmp/Mj_outHl_s5.h"
#include "./bmp/Mj_outHl_s6.h"
#include "./bmp/Mj_outHl_s7.h"
#include "./bmp/Mj_outHl_s8.h"
#include "./bmp/Mj_outHl_s9.h"

/* 
*    位置:打出的牌
*    方向:左
*    牌型:筒
*/
#include "./bmp/Mj_outHl_t1.h"
#include "./bmp/Mj_outHl_t2.h"
#include "./bmp/Mj_outHl_t3.h"
#include "./bmp/Mj_outHl_t4.h"
#include "./bmp/Mj_outHl_t5.h"
#include "./bmp/Mj_outHl_t6.h"
#include "./bmp/Mj_outHl_t7.h"
#include "./bmp/Mj_outHl_t8.h"
#include "./bmp/Mj_outHl_t9.h"

/* 
*    位置:打出的牌
*    方向:左
*    牌型:万
*/
#include "./bmp/Mj_outHl_w1.h"
#include "./bmp/Mj_outHl_w2.h"
#include "./bmp/Mj_outHl_w3.h"
#include "./bmp/Mj_outHl_w4.h"
#include "./bmp/Mj_outHl_w5.h"
#include "./bmp/Mj_outHl_w6.h"
#include "./bmp/Mj_outHl_w7.h"
#include "./bmp/Mj_outHl_w8.h"
#include "./bmp/Mj_outHl_w9.h"

/* 
*    位置:打出的牌
*    方向:右
*    牌型:条
*/
#include "./bmp/Mj_outHr_s1.h"
#include "./bmp/Mj_outHr_s2.h"
#include "./bmp/Mj_outHr_s3.h"
#include "./bmp/Mj_outHr_s4.h"
#include "./bmp/Mj_outHr_s5.h"
#include "./bmp/Mj_outHr_s6.h"
#include "./bmp/Mj_outHr_s7.h"
#include "./bmp/Mj_outHr_s8.h"
#include "./bmp/Mj_outHr_s9.h"

/* 
*    位置:打出的牌
*    方向:右
*    牌型:筒
*/
#include "./bmp/Mj_outHr_t1.h"
#include "./bmp/Mj_outHr_t2.h"
#include "./bmp/Mj_outHr_t3.h"
#include "./bmp/Mj_outHr_t4.h"
#include "./bmp/Mj_outHr_t5.h"
#include "./bmp/Mj_outHr_t6.h"
#include "./bmp/Mj_outHr_t7.h"
#include "./bmp/Mj_outHr_t8.h"
#include "./bmp/Mj_outHr_t9.h"

/* 
*    位置:打出的牌
*    方向:右
*    牌型:万
*/
#include "./bmp/Mj_outHr_w1.h"
#include "./bmp/Mj_outHr_w2.h"
#include "./bmp/Mj_outHr_w3.h"
#include "./bmp/Mj_outHr_w4.h"
#include "./bmp/Mj_outHr_w5.h"
#include "./bmp/Mj_outHr_w6.h"
#include "./bmp/Mj_outHr_w7.h"
#include "./bmp/Mj_outHr_w8.h"
#include "./bmp/Mj_outHr_w9.h"

/* 
*    位置:打出的牌
*    方向:上
*    牌型:条
*/
#include "./bmp/Mj_outHu_s1.h"
#include "./bmp/Mj_outHu_s2.h"
#include "./bmp/Mj_outHu_s3.h"
#include "./bmp/Mj_outHu_s4.h"
#include "./bmp/Mj_outHu_s5.h"
#include "./bmp/Mj_outHu_s6.h"
#include "./bmp/Mj_outHu_s7.h"
#include "./bmp/Mj_outHu_s8.h"
#include "./bmp/Mj_outHu_s9.h"

/* 
*    位置:打出的牌
*    方向:上
*    牌型:筒
*/
#include "./bmp/Mj_outHu_t1.h"
#include "./bmp/Mj_outHu_t2.h"
#include "./bmp/Mj_outHu_t3.h"
#include "./bmp/Mj_outHu_t4.h"
#include "./bmp/Mj_outHu_t5.h"
#include "./bmp/Mj_outHu_t6.h"
#include "./bmp/Mj_outHu_t7.h"
#include "./bmp/Mj_outHu_t8.h"
#include "./bmp/Mj_outHu_t9.h"

/* 
*    位置:打出的牌
*    方向:上
*    牌型:万
*/
#include "./bmp/Mj_outHu_w1.h"
#include "./bmp/Mj_outHu_w2.h"
#include "./bmp/Mj_outHu_w3.h"
#include "./bmp/Mj_outHu_w4.h"
#include "./bmp/Mj_outHu_w5.h"
#include "./bmp/Mj_outHu_w6.h"
#include "./bmp/Mj_outHu_w7.h"
#include "./bmp/Mj_outHu_w8.h"
#include "./bmp/Mj_outHu_w9.h"

/*   公共牌 */

#include "./bmp/MjCard_common_B2.h"
#include "./bmp/MjCard_common_B6.h"
/* 未摸的牌-- 水平 */
#include "./bmp/MjCard_common_backH.h"
/* 未摸的牌-- 垂直 */
#include "./bmp/MjCard_common_backV.h"
/* 左边对手的牌 */
#include "./bmp/MjCard_common_inL.h"
/* 右边对手的牌 */
#include "./bmp/MjCard_common_inR.h"
/* 上边对手的牌 */
#include "./bmp/MjCard_common_inU.h"
/* 右边对手的牌的顶部 */
#include "./bmp/MjCard_common_inRu.h"



#endif /* _MAJIANG_BMP_H_ */

