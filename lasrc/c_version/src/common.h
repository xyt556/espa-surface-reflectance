#ifndef _COMMON_H_
#define _COMMON_H_

#include "hdf.h"
#include "mfhdf.h"
typedef char byte;

#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

/* Surface reflectance version */
#define SR_VERSION "1.2.0"

/* How many lines of data should be processed at one time */
#define PROC_NLINES 1000

/* For angle conversions -
   degrees to radians = PI/180
   radians to degrees = 180/PI */
#define PI 3.14159265
#define PIx2 (PI * 2.0)
#define DEG2RAD 0.017453293
#define RAD2DEG 57.29577951

/* For divisions - to minimize processing time */
#define ONE_DIV_1013 0.000987166
#define ONE_DIV_8500 0.000117647

/* Number of bands corrected to surface reflectance (bands 1-7).  The
   atmospheric correction variables store information for 8 bands, so we will
   go with that for the array size. */
#define NSR_BANDS 8

/* L8 Level-1 products have 8 reflectance bands (bands 1-7, and 9),
   2 thermal bands (band 10 and 11), 1 pan band (band 8), and 1 QA band
   (band 12) */
#define NBAND_REFL_MAX 8
#define NBAND_THM_MAX 2
#define NBAND_PAN_MAX 1
#define NBAND_QA_MAX 1
#define NBAND_TTL_MAX (NBAND_REFL_MAX + NBAND_THM_MAX + NBAND_PAN_MAX + NBAND_QA_MAX)

/* L8 surface reflectance products have 8 reflectance bands, 2 thermal bands, 
   0 pan bands, and 1 QA band */
#define NBAND_REFL_OUT 8
#define NBAND_THM_OUT 2
#define NBAND_PAN_OUT 0
#define NBAND_QA_OUT 1
#define NBAND_TTL_OUT (NBAND_REFL_OUT + NBAND_THM_OUT + NBAND_PAN_OUT + NBAND_QA_OUT)

/* CMG and DEM files are lat/long images where each pixel represents 0.05 deg x
   0.05 deg */
/* DEM information */
#define DEM_NBLAT 3600
#define DEM_NBLON 7200

/* Ratio file information */
#define RATIO_NBLAT 3600
#define RATIO_NBLON 7200

/* Ozone and water vapor information */
#define CMG_NBLAT 3600
#define CMG_NBLON 7200

/* Define the input products to be processed.  NOTE: DN_TTL should be the same
   as NBAND_TTL_MAX. */
typedef enum {DN_BAND1=0, DN_BAND2, DN_BAND3, DN_BAND4, DN_BAND5, DN_BAND6,
    DN_BAND7, DN_BAND8, DN_BAND9, DN_BAND10, DN_BAND11, DN_QA, DN_TTL}
    Mydn_band_t;

/* Define the output products to be processed. NOTE: SR_TTL should be the same
   as NBAND_TTL_OUT */
typedef enum {SR_BAND1=0, SR_BAND2, SR_BAND3, SR_BAND4, SR_BAND5, SR_BAND6,
    SR_BAND7, SR_BAND9, SR_BAND10, SR_BAND11, SR_AEROSOL, SR_TTL} Mysr_band_t;

/* Definte the RADSAT band */
#define SR_RADSAT 0

/* Bit values of ipflag (interpolation flag) QA, which includes aerosol
   levels */
typedef enum {
  IPFLAG_FILL=0,            /* fill value */
  IPFLAG_CLEAR=1,           /* aerosol retrieval was valid (land pixel) */
  IPFLAG_INTERP=2,          /* aerosol was interpolated (water pixel) */
  IPFLAG_WATER=3,           /* water pixel (aerosol retrieval will be redone
                               using subaeroretwat) */
  IPFLAG_RETRIEVAL_FAIL=4,  /* water retrieval failed -- needs interpolated
                               (all failed retrieval pixels are interpolated,
                                thus this is really a temporary/internal use
                                only bit) */
  IPFLAG_TMP_NEIGHBOR=5,    /* flag this pixel as a neighbor of failed aero
                               (internal use only) */
  AERO1_QA=6,    /* these two AERO bits mark the amount of aerosols and = 64 */
  AERO2_QA=7     /* reflect the level of atmospheric correction made    = 128 */
} Ipflag_t;

/* Satellite type definitions, mainly to allow future satellites to be
   supported if needed */
typedef enum {
  SAT_NULL = -1,
  SAT_LANDSAT_8 = 0, 
  SAT_MAX
} Sat_t;

/* Instrument type definition */
typedef enum {
  INST_NULL = -1,
  INST_OLI_TIRS = 0, 
  INST_OLI, 
  INST_MAX
} Inst_t;

/* World Reference System (WRS) type definition */
typedef enum {
  WRS_NULL = -1,
  WRS_1 = 0, 
  WRS_2,
  WRS_MAX
} Wrs_t;

typedef struct {
  int nlines;
  int nsamps;
  double pixsize[2];
} Img_coord_info_t;

#endif
