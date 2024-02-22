/*
 * RCC_program.c
 *
 *  Created on: Aug 9, 2023
 *      Author: mohammedhamdy32
 */


#include "std_types.h"
#include "common_macros.h"

#include "RCC_private.h"
#include "RCC_interface.h"
#include "RCC_config.h"



/*********************************************************************************/
/* Api Name       :    RCC_voidInitSysCls                                        */
/* Parameters in  :    void                                                      */
/* Parameters out :    void                                                      */
/* Description    :    This function init the RCC module                        */
/*********************************************************************************/
void RCC_voidInitSysCls(void)
{

#if RCC_CLK_SRC == HSI  /* Internal clock */

	/* choose system clock */
	CLEAR_BIT(RCC_CFGR,SW0);
	CLEAR_BIT(RCC_CFGR,SW1);

	CLEAR_BIT(RCC_CR , HSEON );
	CLEAR_BIT(RCC_CR , PLLON );
	SET_BIT(  RCC_CR , HSION );



#elif RCC_CLK_SRC == HSE_CRYSTAL

	/* choose system clock */
	SET_BIT(RCC_CFGR,SW0);
	CLEAR_BIT(RCC_CFGR,SW1);

	CLEAR_BIT(RCC_CR , HSION );
	CLEAR_BIT(RCC_CR , PLLON );
	SET_BIT(  RCC_CR , HSEON );



#elif RCC_CLK_SRC == HSE_EXTERNAL_CLK

	SET_BIT(RCC_CR , HSEBYP);  /* open bypass */

	SET_BIT(  RCC_CR , HSEON );
	CLEAR_BIT(RCC_CR , HSION );
	CLEAR_BIT(RCC_CR , PLLON );

	/* choose system clock */
	SET_BIT(RCC_CFGR,SW0);
	CLEAR_BIT(RCC_CFGR,SW1);


#elif RCC_CLK_SRC == PLL_HSI || RCC_CLK_SRC == PLL_HSE

	RCC_PLLCFGR = (RCC_PLLCFGR & 0x7FC0 ) | ( PLL_MULTIPLICATION_FACTOR_FOR_VCO << PLLN );  /* configurate the PLL scaling value */
	/* choose system clock */
	SET_BIT(RCC_CFGR,SW1);
	CLEAR_BIT(RCC_CFGR,SW0);

#if RCC_CLK_SRC == PLL_HSI
	CLEAR_BIT( RCC_PLLCFGR , PLLSRC );  /* choose HSI as an input to PLL */
#elif RCC_CLK_SRC == PLL_HSE
	SET_BIT( RCC_PLLCFGR , PLLSRC );    /* choose HSE as an input to PLL */
#endif

	CLEAR_BIT(RCC_CR , HSION );
	CLEAR_BIT(RCC_CR , HSEON );
	SET_BIT( RCC_CR , PLLON );  /* finally enable PLL */

#else
#error "Not suitable clock selected in init"
#endif

}


/*********************************************************************************/
/* Api Name       :    RCC_voidEnablePerpheralClk                                */
/* Parameters in  :    BusID , PerpheralId                                       */
/* Parameters out :    void                                                      */
/* Description    :    This function enable the perpheral clock                  */
/*********************************************************************************/
void RCC_voidEnablePerpheralClk(u8 BusId , u8 PerpheralId )
{
	if( BusId > MAX_BUSE_NUMBER || PerpheralId > MAX_PERIPHERAL_PER_BUS )
	{
		/* Do nothing */
	}else
	{
		switch( BusId )
		{
		case AHB1:

			SET_BIT( RCC_AHB1ENR , PerpheralId );
			break;
		case AHB2:
			SET_BIT( RCC_AHB2ENR , PerpheralId );
			break;
		case APB1:
			SET_BIT( RCC_APB1ENR , PerpheralId );
			break;
		case APB2:
			SET_BIT( RCC_APB2ENR , PerpheralId );
			break;

		}
	}

}

/*********************************************************************************/
/* Api Name       :    RCC_voidDisablePerpheralClk                               */
/* Parameters in  :    BusID , PerpheralId                                       */
/* Parameters out :    void                                                      */
/* Description    :    This function Disable the perpheral clock                 */
/*********************************************************************************/
void RCC_voidDisablePerpheralClk(u8 BusId , u8 PerpheralId)
{

	if( BusId > MAX_BUSE_NUMBER || PerpheralId > MAX_PERIPHERAL_PER_BUS )
	{
		/* Do nothing */
	}else
	{
		switch( BusId )
		{
		case AHB1:
			CLEAR_BIT( RCC_AHB1ENR , PerpheralId );
			break;
		case AHB2:
			CLEAR_BIT( RCC_AHB2ENR , PerpheralId );
			break;
		case APB1:
			CLEAR_BIT( RCC_APB1ENR , PerpheralId );
			break;
		case APB2:
			CLEAR_BIT( RCC_APB2ENR , PerpheralId );
			break;

		}
	}

}






