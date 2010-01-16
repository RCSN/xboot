/*
 * kernel/fs/devfs/devfs.c
 *
 * Copyright (c) 2007-2009  jianjun jiang <jerryjianjun@gmail.com>
 * website: http://xboot.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <configs.h>
#include <default.h>
#include <types.h>
#include <stdarg.h>
#include <vsprintf.h>
#include <malloc.h>
#include <error.h>
#include <time/xtime.h>
#include <shell/readline.h>
#include <xboot/log.h>
#include <xboot/printk.h>
#include <xboot/initcall.h>
#include <xboot/scank.h>
#include <xboot/chrdev.h>
#include <xboot/blkdev.h>
#include <xboot/device.h>
#include <fs/fs.h>

extern struct device_list * device_list;

/*
 * filesystem operations
 */
static x_s32 devfs_mount(struct mount * m, char * dev, x_s32 flag)
{
	if(dev != NULL)
		return EINVAL;

	m->m_flags = flag & MOUNT_MASK;
	m->m_data = (void *)device_list;

	return 0;
}

static x_s32 devfs_unmount(struct mount * m)
{
	m->m_data = NULL;

	return 0;
}

static x_s32 devfs_sync(struct mount * m)
{
	return 0;
}

static x_s32 devfs_vget(struct mount * m, struct vnode * node)
{
	return 0;
}

static x_s32 devfs_statfs(struct mount * m, struct statfs * stat)
{
	return -1;
}

/*
 * vnode operations
 */
static x_s32 devfs_open(struct vnode * node, x_s32 flag)
{
	struct device * dev;
	struct chrdev * chr;
	struct blkdev * blk;
	x_s8 * path;

	path = (x_s8 *)node->v_path;
	if(!strcmp(path, (const x_s8 *)"/"))
		return 0;

	if(*path == '/')
		path++;

	dev = search_device((const char *)path);
	if(dev == NULL)
		return -1;

	if(dev->type == CHAR_DEVICE)
	{
		chr = (struct chrdev *)(dev->priv);

		if(chr->open(chr) != 0)
			return -1;
	}
	else if(dev->type == BLOCK_DEVICE)
	{
		blk = (struct blkdev *)(dev->priv);

		if(blk->open(blk) != 0)
			return -1;
	}
	else
	{
		return -1;
	}

	/*
	 * store private data
	 */
	node->v_data = (void *)dev;

	return 0;
}

static x_s32 devfs_close(struct vnode * node, struct file * fp)
{
	struct device * dev;
	struct chrdev * chr;
	struct blkdev * blk;
	x_s8 * path;

	path = (x_s8 *)node->v_path;
	if(!strcmp(path, (const x_s8 *)"/"))
		return 0;

	dev = (struct device *)node->v_data;
	if(dev == NULL)
		return -1;

	if(dev->type == CHAR_DEVICE)
	{
		chr = (struct chrdev *)(dev->priv);
		return(chr->close(chr));
	}
	else if(dev->type == BLOCK_DEVICE)
	{
		blk = (struct blkdev *)(dev->priv);
		return(blk->close(blk));
	}

	return -1;
}

static x_s32 devfs_read(struct vnode * node, struct file * fp, void * buf, x_size size, x_size * result)
{
	struct device * dev = (struct device *)(node->v_data);
	struct chrdev * chr;
	struct blkdev * blk;
	x_size len;

	*result = 0;
	if(node->v_type == VDIR)
		return EISDIR;

	if(node->v_type == VCHR)
	{
		chr = (struct chrdev *)(dev->priv);

		len = chr->read(chr, buf, size);
		fp->f_offset = 0;
		*result = len;

		return 0;
	}
	else if(node->v_type == VBLK)
	{
		blk = (struct blkdev *)(dev->priv);

		/* TODO */
		return -1;
	}

	return -1;
}

static x_s32 devfs_write(struct vnode * node , struct file * fp, void * buf, x_size size, x_size * result)
{
	struct device * dev = (struct device *)(node->v_data);
	struct chrdev * chr;
	struct blkdev * blk;
	x_size len;

	*result = 0;
	if(node->v_type == VDIR)
		return EISDIR;

	if(node->v_type == VCHR)
	{
		chr = (struct chrdev *)(dev->priv);

		len = chr->write(chr, buf, size);
		fp->f_offset = 0;
		*result = len;

		return 0;
	}
	else if(node->v_type == VBLK)
	{
		blk = (struct blkdev *)(dev->priv);

		/* TODO */
		return -1;
	}

	return -1;
}

static x_s32 devfs_seek(struct vnode * node, struct file * fp, x_off off1, x_off off2)
{
	if(node->v_type == VBLK)
	{
		if((off2 < 0) || (off2 > (x_off)node->v_size))
			return -1;
		else
			return 0;
	}

	return -1;
}

static x_s32 devfs_ioctl(struct vnode * node, struct file * fp, x_u32 cmd, void * arg)
{
	struct device * dev = (struct device *)(node->v_data);
	struct chrdev * chr;
	struct blkdev * blk;

	if(node->v_type == VDIR)
		return EISDIR;

	if(node->v_type == VCHR)
	{
		chr = (struct chrdev *)(dev->priv);
		return(chr->ioctl(chr, cmd, arg));
	}
	else if(node->v_type == VBLK)
	{
		blk = (struct blkdev *)(dev->priv);
		return(blk->ioctl(blk, cmd, arg));
	}

	return -1;
}

static x_s32 devfs_fsync(struct vnode * node, struct file * fp)
{
	return 0;
}

static x_s32 devfs_readdir(struct vnode * node, struct file * fp, struct dirent * dir)
{
	struct device_list * plist = (struct device_list *)node->v_mount->m_data;
	struct device_list * list;
	struct list_head * pos;
	x_s32 i;

	if(fp->f_offset == 0)
	{
		dir->d_type = DT_DIR;
		strlcpy((x_s8 *)&dir->d_name, (const x_s8 *)".", sizeof(dir->d_name));
	}
	else if(fp->f_offset == 1)
	{
		dir->d_type = DT_DIR;
		strlcpy((x_s8 *)&dir->d_name, (const x_s8 *)"..", sizeof(dir->d_name));
	}
	else
	{
		pos = (&plist->entry)->next;
		for(i = 0; i != (fp->f_offset - 2); i++)
		{
			pos = pos->next;
			if(pos == (&plist->entry))
				return EINVAL;
		}

		list = list_entry(pos, struct device_list, entry);
		if(list->device->type == CHAR_DEVICE)
		{
			dir->d_type = DT_CHR;
		}
		else if(list->device->type == BLOCK_DEVICE)
		{
			dir->d_type = DT_BLK;
		}
		else
		{
			dir->d_type = DT_UNKNOWN;
		}

		strlcpy((x_s8 *)&dir->d_name, (const x_s8 *)list->device->name, sizeof(dir->d_name));
	}

	dir->d_fileno = (x_u32)fp->f_offset;
	dir->d_namlen = (x_u16)strlen((const x_s8 *)dir->d_name);
	fp->f_offset++;

	return 0;
}

static x_s32 devfs_lookup(struct vnode * dnode, char * name, struct vnode * node)
{
	struct device * dev;
	struct chrdev * chr;
	struct blkdev * blk;

	dev = search_device(name);
	if(dev == NULL)
		return -1;

	if(dev->type == CHAR_DEVICE)
	{
		chr = (struct chrdev *)(dev->priv);

		node->v_type = VCHR;
		node->v_size = 0;
	}
	else if(dev->type == BLOCK_DEVICE)
	{
		blk = (struct blkdev *)(dev->priv);

		node->v_type = VBLK;
		node->v_size = blk->blk_num * blk->blk_size;
	}
	else
	{
		return -1;
	}

	node->v_data = (void *)dev;
	node->v_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

	return 0;
}

static x_s32 devfs_create(struct vnode * node, char * name, x_u32 mode)
{
	return -1;
}

static x_s32 devfs_remove(struct vnode * dnode, struct vnode * node, char * name)
{
	return -1;
}

static x_s32 devfs_rename(struct vnode * dnode1, struct vnode * node1, char * name1, struct vnode *dnode2, struct vnode * node2, char * name2)
{
	return -1;
}

static x_s32 devfs_mkdir(struct vnode * node, char * name, x_u32 mode)
{
	return -1;
}

static x_s32 devfs_rmdir(struct vnode * dnode, struct vnode * node, char * name)
{
	return -1;
}

static x_s32 devfs_getattr(struct vnode * node, struct vattr * attr)
{
	return -1;
}

static x_s32 devfs_setattr(struct vnode * node, struct vattr * attr)
{
	return -1;
}

static x_s32 devfs_inactive(struct vnode * node)
{
	return -1;
}

static x_s32 devfs_truncate(struct vnode * node, x_off length)
{
	return -1;
}

/*
 * devfs vnode operations
 */
static struct vnops devfs_vnops = {
	.vop_open 		= devfs_open,
	.vop_close		= devfs_close,
	.vop_read		= devfs_read,
	.vop_write		= devfs_write,
	.vop_seek		= devfs_seek,
	.vop_ioctl		= devfs_ioctl,
	.vop_fsync		= devfs_fsync,
	.vop_readdir	= devfs_readdir,
	.vop_lookup		= devfs_lookup,
	.vop_create		= devfs_create,
	.vop_remove		= devfs_remove,
	.vop_rename		= devfs_rename,
	.vop_mkdir		= devfs_mkdir,
	.vop_rmdir		= devfs_rmdir,
	.vop_getattr	= devfs_getattr,
	.vop_setattr	= devfs_setattr,
	.vop_inactive	= devfs_inactive,
	.vop_truncate	= devfs_truncate,
};

/*
 * file system operations
 */
static struct vfsops devfs_vfsops = {
	.vfs_mount		= devfs_mount,
	.vfs_unmount	= devfs_unmount,
	.vfs_sync		= devfs_sync,
	.vfs_vget		= devfs_vget,
	.vfs_statfs		= devfs_statfs,
	.vfs_vnops		= &devfs_vnops,
};

/*
 * devfs filesystem
 */
static struct filesystem devfs = {
	.name		= "devfs",
	.vfsops		= &devfs_vfsops,
};

static __init void filesystem_devfs_init(void)
{
	if(!filesystem_register(&devfs))
		LOG_E("register 'devfs' filesystem fail");
}

static __exit void filesystem_devfs_exit(void)
{
	if(!filesystem_unregister(&devfs))
		LOG_E("unregister 'devfs' filesystem fail");
}

module_init(filesystem_devfs_init, LEVEL_POSTCORE);
module_exit(filesystem_devfs_exit, LEVEL_POSTCORE);
