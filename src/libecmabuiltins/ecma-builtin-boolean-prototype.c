/* Copyright 2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ecma-alloc.h"
#include "ecma-builtins.h"
#include "ecma-conversion.h"
#include "ecma-exceptions.h"
#include "ecma-gc.h"
#include "ecma-globals.h"
#include "ecma-helpers.h"
#include "ecma-objects.h"
#include "ecma-string-object.h"
#include "ecma-try-catch-macro.h"
#include "globals.h"

#ifndef CONFIG_ECMA_COMPACT_PROFILE_DISABLE_BOOLEAN_BUILTIN

#define ECMA_BUILTINS_INTERNAL
#include "ecma-builtins-internal.h"

#define BUILTIN_INC_HEADER_NAME "ecma-builtin-boolean-prototype.inc.h"
#define BUILTIN_UNDERSCORED_ID boolean_prototype
#include "ecma-builtin-internal-routines-template.inc.h"

/** \addtogroup ecma ECMA
 * @{
 *
 * \addtogroup ecmabuiltins
 * @{
 *
 * \addtogroup booleanprototype ECMA Boolean.prototype object built-in
 * @{
 */

/**
 * The Boolean.prototype object's 'toString' routine
 *
 * See also:
 *          ECMA-262 v5, 15.6.4.2
 *
 * @return completion value
 *         Returned value must be freed with ecma_free_completion_value.
 */
static ecma_completion_value_t
ecma_builtin_boolean_prototype_object_to_string (ecma_value_t this) /**< this argument */
{
  ecma_completion_value_t ret_value;

  ECMA_TRY_CATCH (completion_value_of,
                  ecma_builtin_boolean_prototype_object_value_of (this),
                  ret_value);

  ecma_string_t *ret_str_p;

  if (ecma_is_completion_value_normal_true (completion_value_of))
  {
    ret_str_p = ecma_get_magic_string (ECMA_MAGIC_STRING_TRUE);
  }
  else
  {
    JERRY_ASSERT (ecma_is_completion_value_normal_false (completion_value_of));

    ret_str_p = ecma_get_magic_string (ECMA_MAGIC_STRING_FALSE);
  }

  ret_value = ecma_make_normal_completion_value (ecma_make_string_value (ret_str_p));

  ECMA_FINALIZE (completion_value_of);

  return ret_value;
} /* ecma_builtin_boolean_prototype_object_to_string */

/**
 * The Boolean.prototype object's 'valueOf' routine
 *
 * See also:
 *          ECMA-262 v5, 15.6.4.3
 *
 * @return completion value
 *         Returned value must be freed with ecma_free_completion_value.
 */
static ecma_completion_value_t
ecma_builtin_boolean_prototype_object_value_of (ecma_value_t this) /**< this argument */
{
  if (ecma_is_value_boolean (this))
  {
    return ecma_make_normal_completion_value (this);
  }
  else if (ecma_is_value_object (this))
  {
    ecma_object_t *obj_p = ECMA_GET_NON_NULL_POINTER (this.value);

    ecma_property_t *class_prop_p = ecma_get_internal_property (obj_p, ECMA_INTERNAL_PROPERTY_CLASS);

    if (class_prop_p->u.internal_property.value == ECMA_MAGIC_STRING_BOOLEAN_UL)
    {
      ecma_property_t *prim_value_prop_p = ecma_get_internal_property (obj_p,
                                                                       ECMA_INTERNAL_PROPERTY_PRIMITIVE_BOOLEAN_VALUE);

      JERRY_ASSERT (prim_value_prop_p->u.internal_property.value < ECMA_SIMPLE_VALUE__COUNT);

      ecma_simple_value_t prim_simple_value = prim_value_prop_p->u.internal_property.value;

      ecma_value_t ret_boolean_value = ecma_make_simple_value (prim_simple_value);

      JERRY_ASSERT (ecma_is_value_boolean (ret_boolean_value));

      return ecma_make_normal_completion_value (ret_boolean_value);
    }
  }

  return ecma_make_throw_obj_completion_value (ecma_new_standard_error (ECMA_ERROR_TYPE));
} /* ecma_builtin_boolean_prototype_object_value_of */

/**
 * @}
 * @}
 * @}
 */

#endif /* !CONFIG_ECMA_COMPACT_PROFILE_DISABLE_BOOLEAN_BUILTIN */
