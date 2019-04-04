/*
 * 乱数発生プログラム
 *                      by K.Hoshi
 * usage : rand [-m][-z][-n]|[-h] maxnum neednum
 */
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/types.h>
#include	<time.h>

main( argc, argv )
int 	argc ;
char	*argv[] ;
{
	extern	char	*optarg ;
	extern	int 	optind ;
	extern	int 	opterr ;
/*	double	drand48( ) ;
	double	srand48( ) ;
*/
	double	randbuff ;
	long	max ;
	long	need ;
	long	ci ;
	long	cj ;
	long	getno ;
	long	ret ;
	long	*pnewnum ;
	long	*pnum ;
	time_t	clock ;
	char	*paddr ;
	short	errflg ;
	short	mflg ;
	short	zflg ;
	short	nflg ;
	short	dub ;
	short	keta ;
	char	buffer[40] ;
	mflg = 0 ;
	zflg = 0 ;
	nflg = 0 ;
	errflg = 0 ;
	while( ( ret = getopt( argc, argv, "mznh" ) ) != EOF ) {
		switch( ret ) {
		case 'm' :
			mflg++ ;
			break ;
		case 'z' :
			zflg++ ;
			break ;
		case 'n' :
			nflg++ ;
			break ;
		case 'h' :
			(void)printf( "  usage : rand [-m][-z][-n]|[-h] maxnum neednum\n" )	;
			(void)printf( "     -m : 一度出した番号は出さないモード\n" ) ;
			(void)printf( "     -z : 0 つける  ふつ～  0 なし\n" ) ;
			(void)printf( "     -n : 改行あり  ふつ～  改行なし\n" ) ;
			(void)printf( "     -h : このヘルプ\n" ) ;
			(void)printf( " maxnum : 乱数の最大値\n" ) ;
			(void)printf( "neednum : 必要数\n" ) ;
			(void)printf( "  乱数発生プログラム  by K.Hoshi\n" ) ;
			exit( 0 ) ;
		case '?' :
			errflg++ ;
			break ;
		}
	}
	if( errflg != 0 || argc != optind+2 ) {
		(void)fprintf( stderr, "usage : rand [-m][-z][-n]|[-h] maxnum neednum\n" )	;
		exit( 0 ) ;
	}
	max = atoi( argv[optind] ) ; 
	need = atoi( argv[optind+1] ) ; 
	if( mflg != 0 && max < need ) {
		(void)fprintf( stderr, "そんなのできないよ！\n" )  ;
		exit( 0 ) ;
	}
	(void)time( &clock ) ;
	srand48( clock ) ;
	if( mflg ) {
		paddr = (char *)malloc( (uint)max * 4 ) ;
		pnewnum = (long *)paddr ;
	}
	if( zflg ) {
		(void)sprintf( &buffer[0], "%d\0", max ) ;
		keta = strlen( &buffer[0] ) ;
	}
	for( ci = 0 ; ci < need ; ci++ ) {
		randbuff = drand48( ) ;
		getno = randbuff * (max+1) ;
		if( getno <= 0 || max < getno ) {
			ci-- ;
			continue ;
		}
		if( mflg ) {
			pnum = (long *)paddr ;
			dub = 0 ;
			for( cj = 0 ; cj < ci ; cj++, pnum++ ) {
				if( getno == *pnum ) {
					ci-- ;
					dub = 1 ;
					break ; ;
				}
			}
			if( dub == 1 ) {
				continue ;
			}
			*pnewnum = getno ;
			pnewnum++ ;
		}
		if( zflg ) {
			(void)sprintf( &buffer[0], "%d\0", getno ) ;
			for( cj = 0 ; cj < ( keta - strlen( &buffer[0] ) ) ; cj++ ) {
				(void)printf( "0" ) ;
			}
		}
		(void)printf( "%d ", getno ) ;
		if( nflg ) {
			(void)printf( "\n" ) ;
		}
	}
	if( mflg ) {
		free( paddr ) ;
	}
	exit( 0 ) ;
}
