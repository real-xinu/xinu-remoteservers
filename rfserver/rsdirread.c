/* rsdirread.c - rsdirread */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <dirent.h>

#include "xinudefs.h"
#include "rfilesys.h"
#include "rfserver.h"

extern	void*	memset(void *, int, size_t);

/*------------------------------------------------------------------------
 * rsdirread - handle a directory read request
 *------------------------------------------------------------------------
 */
void	rsdirread (
	 struct	rf_msg_rreq *reqptr,	/* Read request pointer		*/
	 struct	rf_msg_rres *resptr	/* Read response pointer	*/
	)
{
	struct	dirent *dentry;		/* An entry in the directory	*/
	char	*to, *from;		/* used to copy names		*/
	int	len;			/* number of byte in name	*/


	if(findex < 0) {
		snderr( (struct rf_msg_hdr *)reqptr,
			 (struct rf_msg_hdr *)resptr,
			 sizeof(struct rf_msg_rreq) );
		return;
	}

	memset(resptr->rf_data, NULLCH, RF_DATALEN);
	dentry = readdir(ofiles[findex].dirptr);
	if(dentry != NULL) {
		len = 1;
		to = resptr->rf_data;
		from = dentry->d_name;
		while(*to++ = *from++) {
			len++;
		}
		resptr->rf_len = htonl(len);
		sndok( (struct rf_msg_hdr *)reqptr,
		       (struct rf_msg_hdr *)resptr,
		       sizeof(struct rf_msg_rres) );
	}
	else {
		resptr->rf_len = htonl(0);
		sndok( (struct rf_msg_hdr *)reqptr,
		        (struct rf_msg_hdr *)resptr,
			sizeof(struct rf_msg_rres) );
	}

	return;
}
