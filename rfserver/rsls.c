
struct  rf_msg_lreq     {               /* Remote file rmdir request    */
        RF_MSG_HDR                      /* Header fields                */
        uint32  rf_offset;              /* Starting position in listing */
};


struct  rf_msg_lres     {               /* Remote file rmdir response   */
        RF_MSG_HDR                      /* Header fields                */
        uint32  rf_offset;              /* Starting positionn listing   */
        uint32  rf_len;                 /* Number of bytes that follow  */
                                        /*   (0 if no more)             */
        char    rf_list[RF_DATALEN];    /* Array containing rf_len bytes*/
                                        /*   from the listing           */
};


/* rsls.c - rsls */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>

#include "xinudefs.h"
#include "rfilesys.h"
#include "rfserver.h"

extern	void*	memset(void *, int, size_t);

/*------------------------------------------------------------------------
 * rsls - handle a ls request
 *------------------------------------------------------------------------
 */
void	rsls (
	 struct	rf_msg_lreq *reqptr,	/* ptr to ls request		*/
	 struct	rf_msg_lres *resptr	/* ptr to ls response		*/
	)
{
	int	nbytes;			/* number of bytes read from	*/
					/*   the listing		*/
	
	


	/* Zero response buffer to start */

        memset(resptr->rf_list, NULLCH, RF_DATALEN);

        nbytes = read(fd, resptr->rf_data, ntohl(reqptr->rf_len));

#ifdef DEBUG
        printf("DEBUG: read from desc %d specified file returns %d \n",
                        fd, nbytes);
#endif
        
        if (nbytes < 0) {
                resptr->rf_pos = reqptr->rf_pos;
                resptr->rf_len = 0; /* set length to zero */
                snderr( (struct rf_msg_hdr *)reqptr,
                        (struct rf_msg_hdr *)resptr,
                        sizeof(struct rf_msg_rreq) );
                return;
        }

        /* set bytes read */
        
        resptr->rf_pos = reqptr->rf_pos;
        resptr->rf_len = htonl(nbytes);
        sndok(  (struct rf_msg_hdr *)reqptr,
                (struct rf_msg_hdr *)resptr,
                sizeof(struct rf_msg_rres) );
        return;

	return;
}
