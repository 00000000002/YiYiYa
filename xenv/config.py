# coding:utf-8
# *******************************************************************
# * Copyright 2021-2080 evilbinary
# * 作者: evilbinary on 01/01/20
# * 邮箱: rootdebug@163.com
# ********************************************************************
# default libc 默认libc 选择
default_libc='libc'# libmusl libc

# board select platform,选择你要编译的平台
platform='dmulator' ##dmulator pc v3s raspi2 esp32 stm32f4xx raspi3 rk3128 cubieboard2 dummy

# 是否要构建应用
default_apps=True

# gcc path,这里是默认的gcc配置，使用的时候可以启用一下面配置实例注释
CC_PREFIX=''
CC_PATH=''
CC_LIB_PATH=''

CC='gcc'
LD='ld'
AR='ar'
AS='as'
CXX='cxx'
STRIP='strip'
RANLIB='ranlib'
OBJCOPY='objcopy'
CFLAGS=''
ARFLAGS='rc'
OBJCOPYFLAGS=' -S -g'
LINKFLAGS='-nostdlib -nostartfiles -e start  -g '
LINKLD='-Map=kernel.map -T xlinker/link.ld'

# ******************************************************************** #

## oxs x86 duck 配置实例
CC_PREFIX='i386-elf-'
CC='i386-elf-gcc'
CC_LIB_PATH ='/opt/local/lib/gcc/i386-elf/9.2.0/' 
AR='i386-elf-ar'
LD='i386-elf-ld'
AR='i386-elf-ar'
OBJCOPY='i386-elf-objcopy'
RANLIB='i386-elf-ranlib'
CFLAGS='-march=i486'
default_apps=False

## osx arm 配置实例
# CC_PATH=''
# CC_PREFIX='arm-none-eabi-'
# CC_LIB_PATH='/opt/local/lib/gcc/arm-none-eabi/9.2.0/' 

## osx i368 配置实例

# CC_PREFIX='i386-elf-'
# CC='i386-elf-gcc'
# CC_LIB_PATH ='/opt/local/lib/gcc/i386-elf/9.2.0/' 
# AR='i386-elf-ar'
# LD='i386-elf-ld'
# AR='i386-elf-ar'
# OBJCOPY='i386-elf-objcopy'
# RANLIB='i386-elf-ranlib'
# CFLAGS='-march=i486'


## windows arm 配置实例

# CC_PATH=''
# CC_PREFIX='arm-none-eabi-'
# CC_LIB_PATH='D:\\Program Files\\gcc-arm-none-eabi-9\\lib\\gcc\\arm-none-eabi\\9.2.1\\'

## windows i386 配置实例

# CC_PATH=''
# CC_PREFIX='i686-elf-'
# CC_LIB_PATH ='D:\\app\\gcc\\lib\\gcc\\i686-elf\\7.1.0\\' 

## windows arm 配置实例 

# CC_PATH=''
# CC_PREFIX='i686-elf-'
# CC_LIB_PATH ='D:\\app\\gcc\\lib\\gcc\\i686-elf\\7.1.0\\' 

## osx xteansa 配置实例

# CC_PATH='~/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/'
# CC_PREFIX='xtensa-esp32-elf-gcc'
# CC_LIB_PATH='/Users/evil/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/lib/gcc/xtensa-esp32-elf/8.4.0/' 
