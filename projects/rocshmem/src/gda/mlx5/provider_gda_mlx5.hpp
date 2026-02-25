/******************************************************************************
 * Copyright (c) Advanced Micro Devices, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *****************************************************************************/

#ifndef LIBRARY_SRC_GDA_MLX5_GDA_PROVIDER_HPP_
#define LIBRARY_SRC_GDA_MLX5_GDA_PROVIDER_HPP_

extern "C" {
#include "gda/mlx5/mlx5dv.h"
#include "gda/mlx5/mlx5_ifc.h"
}

namespace rocshmem {

typedef union db_reg {
  uint64_t *ptr;
  uintptr_t uint;
} db_reg_t;

struct mlx5dv_funcs_t {
  int (*init_obj)(struct mlx5dv_obj *obj, uint64_t obj_type);
  struct mlx5dv_devx_obj * (*devx_obj_create)(
      struct ibv_context *context, const void *in, size_t inlen, void *out, size_t outlen);
  int (*devx_obj_modify)(
      struct mlx5dv_devx_obj *obj, const void *in, size_t inlen, void *out, size_t outlen);
  int (*devx_obj_destroy)(struct mlx5dv_devx_obj *obj);
  struct mlx5dv_devx_uar * (*devx_alloc_uar)(struct ibv_context *context, uint32_t flags);
  void (*devx_free_uar)(struct mlx5dv_devx_uar *devx_uar);
  struct mlx5dv_devx_umem * (*devx_umem_reg_ex)(
      struct ibv_context *ctx, struct mlx5dv_devx_umem_in *umem_in);
  int (*devx_umem_dereg)(struct mlx5dv_devx_umem *umem);
};

struct mlx5_devx_qp {
  ibv_context*      ctx;
  mlx5dv_devx_obj*  devx_obj;
  mlx5dv_devx_uar*  uar;
  mlx5dv_devx_umem* umem;
  void*             sq;
  uint32_t*         dbrec;
  uint32_t          qpn;
  uint16_t          sq_depth;

  int create(const mlx5dv_funcs_t& mlx5dv, struct ibv_context *ctx,
             struct ibv_qp_init_attr_ex *attr);
  int modify(const mlx5dv_funcs_t& mlx5dv, struct ibv_qp_attr *attr, int attr_mask,
             uint32_t gid_type);
  int destroy(const mlx5dv_funcs_t& mlx5dv);
  void dump(int conn_num);
};

}  // namespace rocshmem

#endif  //LIBRARY_SRC_GDA_MLX5_GDA_PROVIDER_HPP_
