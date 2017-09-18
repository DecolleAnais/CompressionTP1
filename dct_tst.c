#include "bases.h"
#include "matrice.h"
#include "dct.h"

#define NBE 5

void coef_dct_tst()
{
  Matrice *table ;
  int i, j ;
  static float t[NBE][NBE] =
  {
    { 0.447214, 0.447214, 0.447214   , 0.447214, 0.447214},
    { 0.601501, 0.371748, 3.87265e-17,-0.371748,-0.601501},
    { 0.511667,-0.19544 ,-0.632456   ,-0.19544 , 0.511667},
    { 0.371748,-0.601501,-1.1618e-16 , 0.601501,-0.371748},
    { 0.19544 ,-0.511667, 0.632456   ,-0.511667, 0.19544 },
  } ;


  table = allocation_matrice_float(NBE, NBE) ;
  coef_dct(table) ;

  if ( 0 )
    for(j=0; j<NBE; j++)
      {
	printf("{ ") ;
	for(i=0; i<NBE; i++)
	  printf("%s%g", i ? "," : "" , table->t[j][i]) ;
	printf("},\n") ;
      }

  for(j=0; j<NBE; j++)
    for(i=0; i<NBE; i++)
      if ( fabs(table->t[j][i] - t[j][i]) > 0.0001 )
	{
	  eprintf("La matrice est mauvaise.\n") ;
	  eprintf("dct[%d][%d] = %g au lieu de %g\n"
		  , j, i, table->t[j][i], t[j][i]) ;
	  return ;
	}
}

#define BIG 128
#define F(i) (cos(i) + cos(i/4.+.1) + cos(i/7.+2))

void dct_tst()
{
  int i ;
  float entree[BIG], sortie[BIG] ;
  static float dct_ok[BIG] = { 0.356132, -2.04764, 0.520159, -2.62484, 0.589061, -6.79482, 0.0291543, 3.20903, 0.879606, -0.015797, 7.85907, 2.10175, -0.52096, 0.749767, -0.106729, 0.438389, 0.0272217, 0.285856, 0.0978661, 0.193163, 0.145888, 0.129765, 0.18504, 0.0824345, 0.221947, 0.0441666, 0.261113, 0.0105275, 0.306989, -0.0220057, 0.365656, -0.0572386, 0.447654, -0.100983, 0.5752, -0.165547, 0.807283, -0.287972, 1.37412, -0.673005, 4.98071, 4.85425, -2.89189, 0.574326, -1.09303, 0.312993, -0.662694, 0.216802, -0.46941, 0.166029, -0.35958, 0.134286, -0.288758, 0.112374, -0.239309, 0.0962382, -0.202839, 0.0838021, -0.174845, 0.0738904, -0.152688, 0.0657845, -0.134723, 0.059019, -0.119868, 0.0532782, -0.107384, 0.04834, -0.0967472, 0.0440425, -0.0875773, 0.0402657, -0.0795902, 0.0369175, -0.0725703, 0.0339265, -0.0663506, 0.0312366, -0.0607996, 0.0288023, -0.0558127, 0.0265869, -0.051305, 0.0245601, -0.0472078, 0.0226972, -0.0434637, 0.0209769, -0.0400253, 0.0193812, -0.0368528, 0.0178953, -0.0339124, 0.0165059, -0.0311751, 0.0152018, -0.028616, 0.0139732, -0.0262141, 0.0128114, -0.02395, 0.0117086, -0.0218077, 0.0106583, -0.0197726, 0.00965437, -0.0178317, 0.00869123, -0.0159735, 0.00776405, -0.0141872, 0.00686833, -0.0124638, 0.00599973, -0.0107942, 0.00515454, -0.00917073, 0.00432921, -0.00758549, 0.00352026, -0.00603163, 0.00272448, -0.00450244, 0.00193893, -0.00299156, 0.00116054, -0.00149283, 0.000386358 } ;

  for(i=0; i<BIG; i++)
    entree[i] = F(i) ;
  
  dct(0, BIG, entree, sortie) ;

  if ( 0 )
    {
      for(i=0; i<BIG; i++)
	printf(", %g", sortie[i]) ;
      printf("\n") ;
    }

  for(i=0; i<BIG; i++)
    if ( fabs(sortie[i] - dct_ok[i]) > 0.0001 )
      {
	eprintf("La dct est mauvaise.\n") ;
	eprintf("sortie[%d] = %g au lieu de %g\n"
		, i, sortie[i], dct_ok[i]) ;
	return ;
      }

  for(i=0; i<BIG; i++)
    entree[i] = 10 ;
  dct(1, BIG, sortie, entree) ;

  for(i=0; i<BIG; i++)
    if ( fabs(entree[i] - F(i)) > 0.01 )
      {
	eprintf("La dct inverse est mauvaise.\n") ;
	eprintf("sortie[%d] = %g au lieu de %g\n"
		, i, entree[i], F(i)) ;
	return ;
      }
}

