/**
  ******************************************************************************
  * File Name          : debug_string.h
  * Description        : 
  ******************************************************************************
  *
**/

#ifndef __DEBUG_STRING__
#define __DEBUG_STRING__

#define DEBUG_STRING_LEVEL_ERROR                         0x00000001
#define DEBUG_STRING_LEVEL_WARN                          0x00000002
#define DEBUG_STRING_LEVEL_DEBUG                         0x00000004
#define DEBUG_STRING_LEVEL_INFO1                         0x00000010
#define DEBUG_STRING_LEVEL_INFO2                         0x00000020
#define DEBUG_STRING_LEVEL_INFO3                         0x00000040
#define DEBUG_STRING_LEVEL_INFO4                         0x00000080


#define debug_output_str_error(fmt, ...)                                         \
   do                                                                            \
   {                                                                             \
      if (MODULE_DEBUG_LEVEL & DEBUG_STRING_LEVEL_ERROR)                         \
      {                                                                          \
         printf(" [%s-%d] " fmt,                                                 \
                                 __func__, __LINE__, ##__VA_ARGS__);             \
      }                                                                          \
   } while (0)

#define debug_output_str_warn(fmt, ...)                                          \
   do                                                                            \
   {                                                                             \
      if (MODULE_DEBUG_LEVEL & DEBUG_STRING_LEVEL_WARN)                          \
      {                                                                          \
         printf(" [%s-%d] " fmt,                                                 \
                                 __func__, __LINE__, ##__VA_ARGS__);             \
      }                                                                          \
   } while (0)

#define debug_output_str_debug(fmt, ...)                                         \
   do                                                                            \
   {                                                                             \
      if (MODULE_DEBUG_LEVEL & DEBUG_STRING_LEVEL_DEBUG)                         \
      {                                                                          \
         printf(" [%s-%d] " fmt,                                                 \
                                 __func__, __LINE__, ##__VA_ARGS__);             \
      }                                                                          \
   } while (0)

#define debug_output_str_info1(fmt, ...)                                         \
   do                                                                            \
   {                                                                             \
      if (MODULE_DEBUG_LEVEL & DEBUG_STRING_LEVEL_INFO1)                         \
      {                                                                          \
         printf(" [%s-%d] " fmt,                                                 \
                                 __func__, __LINE__, ##__VA_ARGS__);             \
      }                                                                          \
   } while (0)

#define debug_output_str_info2(fmt, ...)                                         \
   do                                                                            \
   {                                                                             \
      if (MODULE_DEBUG_LEVEL & DEBUG_STRING_LEVEL_INFO2)                         \
      {                                                                          \
         printf(" [%s-%d] " fmt,                                                 \
                                 __func__, __LINE__, ##__VA_ARGS__);             \
      }                                                                          \
   } while (0)

#define debug_output_str_info3(fmt, ...)                                         \
   do                                                                            \
   {                                                                             \
      if (MODULE_DEBUG_LEVEL & DEBUG_STRING_LEVEL_INFO3)                         \
      {                                                                          \
         printf(" [%s-%d] " fmt,                                                 \
                                 __func__, __LINE__, ##__VA_ARGS__);             \
      }                                                                          \
   } while (0)

#define debug_output_str_info4(fmt, ...)                                         \
   do                                                                            \
   {                                                                             \
      if (MODULE_DEBUG_LEVEL & DEBUG_STRING_LEVEL_INFO4)                         \
      {                                                                          \
         printf(" [%s-%d] " fmt,                                                 \
                                 __func__, __LINE__, ##__VA_ARGS__);             \
      }                                                                          \
   } while (0)


#endif   // __DEBUG_STRING__

