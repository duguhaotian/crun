/*
 * crun - OCI runtime written in C
 *
 * Copyright (C) 2017 Giuseppe Scrivano <giuseppe@scrivano.org>
 * libocispec is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * libocispec is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with crun.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CONTAINER_H
# define CONTAINER_H

# include <config.h>
# include <oci_runtime_spec.h>
# include "error.h"

struct libcrun_container_s
{
  /* Container parsed from the runtime json file.  */
  oci_container *container_def;

  uid_t host_uid;
  gid_t host_gid;

  uid_t container_uid;
  gid_t container_gid;

  void *private_data;
};

struct libcrun_run_options
{
  char *state_root;
  char *id;
  char *console_socket;
  char *pid_file;
  int preserve_fds;

  int systemd_cgroup : 1;
  int detach : 1;
  int no_subreaper: 1;
  int no_new_keyring : 1;
};

typedef struct libcrun_container_s libcrun_container;

libcrun_container *libcrun_container_load (const char *path, libcrun_error_t *error);

int libcrun_container_run (libcrun_container *container, struct libcrun_run_options *opts, libcrun_error_t *error);

int libcrun_delete_container (const char *state_root, const char *id, int force, libcrun_error_t *err);

int
libcrun_kill_container (const char *state_root, const char *id, int signal, libcrun_error_t *err);

#endif
