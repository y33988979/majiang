#*****************************************************************************
#
# Description: 
#    Makefile for 5197
#
# Revision History:
#    Date          Author         Modification
# ---------------------------------------------------------------------
# 1. 2005-11-30    Qiujordan      创建
# 2. 2009-04-13    Jyshan         for 5197
#*****************************************************************************

## 公共变量与规则
include $(DVD_MAKE)/generic.mak


CC=$(CROSS_COMPILE)g++

## 编译选项
CFLAGS := $(CFLAGS) -DSTTBX_PRINT

## 输入库名
CFLAGS := $(CFLAGS) -fno-rtti -fno-exceptions -fstrict-aliasing

## 输出库名
ST40_EXPORTS := libmajiang.a

## 对象文件列表
OBJS := handcards.o mahjong.o judge.o gamer.o computer.o player.o engine.o painter.o \
majiang.o

## 目标库名
ST40_TARGETS := libmajiang.a

## 缺省变量与规则
include $(DVD_MAKE)/defrules.mak

## 创建目标库
# -------------
$(ST40_TARGETS) : $(ST40_IMPORTS) $(OBJS)
	@$(ECHO) Building $@
	$(BUILD_LIBRARY) -lstd++

handcards.o: handcards.cpp handcards.h
	$(COMPILE_C) 

mahjong.o: mahjong.cpp mahjong.h
	$(COMPILE_C) 

gamer.o: gamer.cpp gamer.h
	$(COMPILE_C) 

computer.o: computer.cpp computer.h
	$(COMPILE_C) 

player.o: player.cpp player.h
	$(COMPILE_C) 

judge.o: judge.cpp judge.h
	$(COMPILE_C) 

engine.o: engine.cpp engine.h
	$(COMPILE_C) 

painter.o: painter.cpp painter.h
	$(COMPILE_C) 

majiang.o: majiang.cpp
	$(COMPILE_C) 
	
clean:
	@$(ECHO) ---- Cleaning digitv ----
	-$(RM) *.o
	-$(RM) *.a

# 依赖关系
