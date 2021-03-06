/*
 * Half-Life Weapon Mod
 * Copyright (c) 2012 - 2014 AGHL.RU Dev Team
 * 
 * http://aghl.ru/forum/ - Russian Half-Life and Adrenaline Gamer Community
 *
 *
 *    This program is free software; you can redistribute it and/or modify it
 *    under the terms of the GNU General Public License as published by the
 *    Free Software Foundation; either version 2 of the License, or (at
 *    your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful, but
 *    WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software Foundation,
 *    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *    In addition, as a special exception, the author gives permission to
 *    link the code of this program with the Half-Life Game Engine ("HL
 *    Engine") and Modified Game Libraries ("MODs") developed by Valve,
 *    L.L.C ("Valve").  You must obey the GNU General Public License in all
 *    respects for all of the code used other than the HL Engine and MODs
 *    from Valve.  If you modify this file, you may extend this exception
 *    to your version of the file, but you are not obligated to do so.  If
 *    you do not wish to do so, delete this exception statement from your
 *    version.
 *
 */

#ifndef _LIBFUNC_H
#define _LIBFUNC_H

#include <extdll.h>
#include <meta_api.h>

#if defined WIN32
	#define NOGDI

	#include <psapi.h>
#else
	#include <dlfcn.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <sys/mman.h>
	#include <unistd.h>

	#define	PAGE_SIZE 4096
	#define Align(addr) (void*)((long)addr & ~(PAGE_SIZE-1))
	
	typedef unsigned long DWORD;
	typedef unsigned short WORD;
	typedef unsigned int UNINT32;
#endif


struct module
{
	void*	base;
	size_t	size;
	void*	handler;
};

struct function
{
	const char*		name;

	void*			address;
	void*			handler;

	unsigned char	patch[5];
	unsigned char	origin[5];

	int				done;
};

bool	SetHook					(function *func);
bool	UnsetHook				(function *func);
bool	AllowWriteToMemory		(void *address);

size_t	FindAdressInDLL			(module *lib, const char *name);
size_t	FindAdressInDLL			(size_t start, size_t end, unsigned char *pattern, char *mask);
size_t	FindStringInDLL			(size_t start, size_t end, const char *string);

int		FindModuleByAddr		(void *addr, module *lib);
int		CreateFunctionHook		(function *func);

#endif // _LIBFUNC_H
