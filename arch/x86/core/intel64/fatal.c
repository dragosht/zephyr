/*
 * Copyright (c) 2019 Intel Corporation
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <ksched.h>
#include <kernel_structs.h>
#include <kernel_internal.h>
#include <logging/log.h>
LOG_MODULE_DECLARE(os);

void z_x86_exception(const z_arch_esf_t *esf)
{
	LOG_ERR("** CPU Exception %ld (code %ld/0x%lx) **",
		esf->vector, esf->code, esf->code);

#ifdef CONFIG_THREAD_STACK_INFO
	if (z_x86_check_stack_bounds(esf->rsp, 0, esf->cs)) {
		z_x86_fatal_error(K_ERR_STACK_CHK_FAIL, esf);
	}
#endif

	z_x86_fatal_error(K_ERR_CPU_EXCEPTION, esf);
}
