
// These are the result codes:
#define ZR_OK         0x00000000     // nb. the pseudo-code zr-recent is never returned,
#define ZR_RECENT     0x00000001     // but can be passed to FormatZipMessage.
#define ZR_GENMASK    0x0000FF00	// The following come from general system stuff (e.g. files not openable)

#define ZR_NODUPH     0x00000100     // couldn't duplicate the handle
#define ZR_NOFILE     0x00000200     // couldn't create/open the file
#define ZR_NOALLOC    0x00000300     // failed to allocate some resource
#define ZR_WRITE      0x00000400     // a general error writing to the file
#define ZR_NOTFOUND   0x00000500     // couldn't find that file in the zip
#define ZR_MORE       0x00000600     // there's still more data to be unzipped
#define ZR_CORRUPT    0x00000700     // the zipfile is corrupt or not a zipfile
#define ZR_READ       0x00000800     // a general error reading the file

#define ZR_CALLERMASK 0x00FF0000		// The following come from mistakes on the part of the caller
#define ZR_ARGS       0x00010000     // general mistake with the arguments
#define ZR_NOTMMAP    0x00020000     // tried to ZipGetMemory, but that only works on mmap zipfiles, which yours wasn't
#define ZR_MEMSIZE    0x00030000     // the memory size is too small
#define ZR_FAILED     0x00040000     // the thing was already failed when you called this function
#define ZR_ENDED      0x00050000     // the zip creation has already been closed
#define ZR_MISSIZE    0x00060000     // the indicated input file size turned out mistaken
#define ZR_PARTIALUNZ 0x00070000     // the file had already been partially unzipped
#define ZR_ZMODE      0x00080000     // tried to mix creating/opening a zip 

#define ZR_BUGMASK    0xFF000000		// The following come from bugs within the zip library itself
#define ZR_NOTINITED  0x01000000     // initialisation didn't work
#define ZR_SEEK       0x02000000     // trying to seek in an unseekable file
#define ZR_NOCHANGE   0x04000000     // changed its mind on storage, but not allowed
#define ZR_FLATE      0x05000000     // an internal error in the de/inflation code

typedef DWORD ZRESULT;

// return codes from any of the zip functions. Listed later.

#define ZIP_HANDLE   1
#define ZIP_FILENAME 2
#define ZIP_MEMORY   3

// unz_global_info structure contain global data about the ZIPfile
typedef struct unz_global_info_s
{ 
	unsigned long number_entry;         // total number of entries in the central dir on this disk
	unsigned long size_comment;         // size of the global comment of the zipfile
} unz_global_info;

#ifndef _TM_DEFINED
struct tm {
        int tm_sec;     /* seconds after the minute - [0,59] */
        int tm_min;     /* minutes after the hour - [0,59] */
        int tm_hour;    /* hours since midnight - [0,23] */
        int tm_mday;    /* day of the month - [1,31] */
        int tm_mon;     /* months since January - [0,11] */
        int tm_year;    /* years since 1900 */
        int tm_wday;    /* days since Sunday - [0,6] */
        int tm_yday;    /* days since January 1 - [0,365] */
        int tm_isdst;   /* daylight savings time flag */
        };
#define _TM_DEFINED
#endif
// unz_file_info contain information about a file in the zipfile
typedef struct unz_file_info_s
{ 
	unsigned long version;              // version made by                 2 bytes
	unsigned long version_needed;       // version needed to extract       2 bytes
	unsigned long flag;                 // general purpose bit flag        2 bytes
	unsigned long compression_method;   // compression method              2 bytes
	unsigned long dosDate;              // last mod file date in Dos fmt   4 bytes
	unsigned long crc;                  // crc-32                          4 bytes
	unsigned long compressed_size;      // compressed size                 4 bytes
	unsigned long uncompressed_size;    // uncompressed size               4 bytes
	unsigned long size_filename;        // filename length                 2 bytes
	unsigned long size_file_extra;      // extra field length              2 bytes
	unsigned long size_file_comment;    // file comment length             2 bytes
	unsigned long disk_num_start;       // disk number start               2 bytes
	unsigned long internal_fa;          // internal file attributes        2 bytes
	unsigned long external_fa;          // external file attributes        4 bytes
	tm tmu_date;
} unz_file_info;


#define UNZ_OK                  (0)
#define UNZ_END_OF_LIST_OF_FILE (-100)
#define UNZ_ERRNO               (Z_ERRNO)
#define UNZ_EOF                 (1)
#define UNZ_PARAMERROR          (-102)
#define UNZ_BADZIPFILE          (-103)
#define UNZ_INTERNALERROR       (-104)
#define UNZ_CRCERROR            (-105)

#define ZLIB_VERSION "1.1.3"


// Allowed flush values; see deflate() for details
#define Z_NO_FLUSH      0
#define Z_SYNC_FLUSH    2
#define Z_FULL_FLUSH    3
#define Z_FINISH        4

// compression levels
#define Z_NO_COMPRESSION         0
#define Z_BEST_SPEED             1
#define Z_BEST_COMPRESSION       9
#define Z_DEFAULT_COMPRESSION  (-1)

// compression strategy; see deflateInit2() for details
#define Z_FILTERED            1
#define Z_HUFFMAN_ONLY        2
#define Z_DEFAULT_STRATEGY    0

// Possible values of the data_type field
#define Z_BINARY   0
#define Z_ASCII    1
#define Z_UNKNOWN  2

// The deflate compression method (the only one supported in this version)
#define Z_DEFLATED   8

// for initializing zalloc, zfree, opaque
#define Z_nullptr  0

// case sensitivity when searching for filenames
#define CASE_SENSITIVE 1
#define CASE_INSENSITIVE 2


// Return codes for the compression/decompression functions. Negative
// values are errors, positive values are used for special but normal events.
#define Z_OK            0
#define Z_STREAM_END    1
#define Z_NEED_DICT     2
#define Z_ERRNO        (-1)
#define Z_STREAM_ERROR (-2)
#define Z_DATA_ERROR   (-3)
#define Z_MEM_ERROR    (-4)
#define Z_BUF_ERROR    (-5)
#define Z_VERSION_ERROR (-6)

// Basic data types
typedef unsigned char  Byte;  // 8 bits
typedef unsigned int   uInt;  // 16 bits or more
typedef unsigned long  uLong; // 32 bits or more
typedef void *voidpf;
typedef void *voidp;
typedef long z_off_t;

typedef voidpf (*alloc_func) (voidpf opaque, uInt items, uInt size);
typedef void   (*free_func)  (voidpf opaque, voidpf address);

////struct internal_state;

typedef struct z_stream_s 
{
	Byte    *next_in;  // next input byte
	uInt     avail_in;  // number of bytes available at next_in
	uLong    total_in;  // total nb of input bytes read so far

	Byte    *next_out; // next output byte should be put there
	uInt     avail_out; // remaining free space at next_out
	uLong    total_out; // total nb of bytes output so far

	char     *msg;      // last error message, nullptr if no error
	struct internal_state *state; // not visible by applications

	alloc_func zalloc;  // used to allocate the internal state
	free_func  zfree;   // used to free the internal state
	voidpf     opaque;  // private data object passed to zalloc and zfree

	int     data_type;  // best guess about the data type: ascii or binary
	uLong   adler;      // adler32 value of the uncompressed data
	uLong   reserved;   // reserved for future use
} z_stream,*z_streamp;

typedef enum {
	TYPE,     // get type bits (3, including end bit)
	LENS,     // get lengths for stored
	STORED,   // processing stored block
	TABLE,    // get table lengths
	BTREE,    // get bit lengths tree for a dynamic block
	DTREE,    // get length, distance trees for a dynamic block
	CODES,    // processing fixed or dynamic block
	DRY,      // output remaining window bytes
	DONE,     // finished last block, done 
	BAD	 // got a data error--stuck here 
}  inflate_block_mode;


#define zmalloc(len)	GlobalAlloc(GPTR,len)		//malloc(len)///
#define zfree(p)		GlobalFree(p)						//	free(p)////

const char * const z_errmsg[10] = {"need dictionary","stream end","","file error","stream error","data error","insufficient memory", "buffer error","incompatible version",""};

#define ERR_MSG(err) z_errmsg[Z_NEED_DICT-(err)]

#define ERR_RETURN(strm,err)	return (strm->msg = (char*)ERR_MSG(err), (err))

#define STORED_BLOCK 0
#define STATIC_TREES 1
#define DYN_TREES    2
// The three kinds of block type 

#define MIN_MATCH  3
#define MAX_MATCH  258
// The minimum and maximum match lengths 

#define PRESET_DICT 0x20 // preset dictionary flag in zlib header 
#define OS_CODE  0x0b  // Window 95 & Windows NT


typedef uLong (*check_func) (uLong check, const Byte *buf, uInt len);
///voidpf zcalloc (voidpf opaque, unsigned items, unsigned size);

#define ZALLOC(strm, items, size) (*((strm)->zalloc))((strm)->opaque, (items), (size))
#define ZFREE(strm, addr)  (*((strm)->zfree))((strm)->opaque, (voidpf)(addr))

#define TRY_FREE(s, p) {if (p) ZFREE(s, p);}

typedef struct inflate_huft_s inflate_huft;

struct inflate_huft_s {
	union {
		struct {
			Byte Exop;        // number of extra bits or operation
			Byte Bits;        // number of bits in this code or subcode
		} what;
		uInt pad;           // pad structure to a power of 2 (4 bytes for
	} word;               //  16-bit, 8 bytes for 32-bit int's)
	uInt base;            // literal, length base, distance base, or table offset
};

// Maximum size of dynamic tree.  The maximum found in a long but non-
//   exhaustive search was 1004 huft structures (850 for length/literals
//   and 154 for distances, the latter actually the result of an
//   exhaustive search).  The actual maximum is not known, but the
//   value below is more than safe.
#define MANY 1440

int inflate_trees_bits (uInt *,                    // 19 code lengths
						uInt *,                    // bits tree desired/actual depth
						inflate_huft * *,       // bits tree result
						inflate_huft *,             // space for trees
						z_streamp);                // for messages

int inflate_trees_dynamic (
						   uInt,                       // number of literal/length codes
						   uInt,                       // number of distance codes
						   uInt *,                    // that many (total) code lengths
						   uInt *,                    // literal desired/actual bit depth
						   uInt *,                    // distance desired/actual bit depth
						   inflate_huft * *,       // literal/length tree result
						   inflate_huft * *,       // distance tree result
						   inflate_huft *,             // space for trees
						   z_streamp);                // for messages

int inflate_trees_fixed (
						 uInt *,                    // literal desired/actual bit depth
						 uInt *,                    // distance desired/actual bit depth
						 const inflate_huft * *,       // literal/length tree result
						 const inflate_huft * *,       // distance tree result
						 z_streamp);                // for memory allocation

struct inflate_blocks_state;
typedef struct inflate_blocks_state inflate_blocks_statef;

struct inflate_codes_state;
typedef struct inflate_codes_state inflate_codes_statef;


// inflate blocks semi-private state 
struct inflate_blocks_state {

	// mode 
	inflate_block_mode  mode;     // current inflate_block mode 

	// mode dependent information 
	union {
		uInt left;          // if STORED, bytes left to copy 
		struct {
			uInt table;               // table lengths (14 bits) 
			uInt index;               // index into blens (or border)
			uInt *blens;             // bit lengths of codes
			uInt bb;                  // bit length tree depth 
			inflate_huft *tb;         // bit length decoding tree 
		} trees;            // if DTREE, decoding info for trees 
		struct {
			inflate_codes_statef 
				*codes;
		} decode;           // if CODES, current state 
	} sub;                // submode
	uInt last;            // true if this block is the last block 

	// mode independent information 
	uInt bitk;            // bits in bit buffer 
	uLong bitb;           // bit buffer 
	inflate_huft *hufts;  // single malloc for tree space 
	Byte *window;        // sliding window 
	Byte *end;           // one byte after sliding window 
	Byte *read;          // window read pointer 
	Byte *write;         // window write pointer 
	check_func checkfn;   // check function 
	uLong check;          // check on output 

};

// defines for inflate input/output
//   update pointers and return 

#define LOAD {p=z->next_in;n=z->avail_in;b=s->bitb;k=s->bitk; q=s->write;m=(uInt)WAVAIL;m;}

#define LEAVE {s->bitb=b;s->bitk=k; z->avail_in=n;z->total_in+=(uLong)(p-z->next_in);z->next_in=p; s->write=q; return inflate_flush(s,z,r);}
//   get bytes and bits 
#define NEEDBYTE {if(n)r=Z_OK;else LEAVE}
#define NEXTBYTE (n--,*p++)
#define NEEDBITS(j) {while(k<(j)){NEEDBYTE;b|=((uLong)NEXTBYTE)<<k;k+=8;}}
#define DUMPBITS(j) {b>>=(j);k-=(j);}
//   output bytes 
#define WAVAIL (uInt)(q<s->read?s->read-q-1:s->end-q)
#define WRAP {if(q==s->end&&s->read!=s->window){q=s->window;m=(uInt)WAVAIL;}}
#define FLUSH {s->write=q; r=inflate_flush(s,z,r); q=s->write;m=(uInt)WAVAIL;m;}
#define NEEDOUT {if(m==0){WRAP if(m==0){FLUSH WRAP if(m==0) LEAVE}}r=Z_OK;}
#define OUTBYTE(a) {*q++=(Byte)(a);m--;}
//   load local pointers 

// masks for lower bits (size given to avoid silly warnings with Visual C++) 
// And'ing with mask[n] masks the lower n bits
const uInt inflate_mask[17] = {0x0000,0x0001, 0x0003, 0x0007, 0x000f, 0x001f, 0x003f, 0x007f, 0x00ff,0x01ff, 0x03ff, 0x07ff, 0x0fff, 0x1fff, 0x3fff, 0x7fff, 0xffff};

// copy as much as possible from the sliding window to the output area
////int inflate_flush (inflate_blocks_statef *, z_streamp, int);

int inflate_fast (uInt, uInt, const inflate_huft *, const inflate_huft *, inflate_blocks_statef *, z_streamp );

const uInt fixed_bl = 9;
const uInt fixed_bd = 5;
const inflate_huft fixed_tl[] = {
    {{{96,7}},256}, {{{0,8}},80}, {{{0,8}},16}, {{{84,8}},115},
    {{{82,7}},31}, {{{0,8}},112}, {{{0,8}},48}, {{{0,9}},192},
    {{{80,7}},10}, {{{0,8}},96}, {{{0,8}},32}, {{{0,9}},160},
    {{{0,8}},0}, {{{0,8}},128}, {{{0,8}},64}, {{{0,9}},224},
    {{{80,7}},6}, {{{0,8}},88}, {{{0,8}},24}, {{{0,9}},144},
    {{{83,7}},59}, {{{0,8}},120}, {{{0,8}},56}, {{{0,9}},208},
    {{{81,7}},17}, {{{0,8}},104}, {{{0,8}},40}, {{{0,9}},176},
    {{{0,8}},8}, {{{0,8}},136}, {{{0,8}},72}, {{{0,9}},240},
    {{{80,7}},4}, {{{0,8}},84}, {{{0,8}},20}, {{{85,8}},227},
    {{{83,7}},43}, {{{0,8}},116}, {{{0,8}},52}, {{{0,9}},200},
    {{{81,7}},13}, {{{0,8}},100}, {{{0,8}},36}, {{{0,9}},168},
    {{{0,8}},4}, {{{0,8}},132}, {{{0,8}},68}, {{{0,9}},232},
    {{{80,7}},8}, {{{0,8}},92}, {{{0,8}},28}, {{{0,9}},152},
    {{{84,7}},83}, {{{0,8}},124}, {{{0,8}},60}, {{{0,9}},216},
    {{{82,7}},23}, {{{0,8}},108}, {{{0,8}},44}, {{{0,9}},184},
    {{{0,8}},12}, {{{0,8}},140}, {{{0,8}},76}, {{{0,9}},248},
    {{{80,7}},3}, {{{0,8}},82}, {{{0,8}},18}, {{{85,8}},163},
    {{{83,7}},35}, {{{0,8}},114}, {{{0,8}},50}, {{{0,9}},196},
    {{{81,7}},11}, {{{0,8}},98}, {{{0,8}},34}, {{{0,9}},164},
    {{{0,8}},2}, {{{0,8}},130}, {{{0,8}},66}, {{{0,9}},228},
    {{{80,7}},7}, {{{0,8}},90}, {{{0,8}},26}, {{{0,9}},148},
    {{{84,7}},67}, {{{0,8}},122}, {{{0,8}},58}, {{{0,9}},212},
    {{{82,7}},19}, {{{0,8}},106}, {{{0,8}},42}, {{{0,9}},180},
    {{{0,8}},10}, {{{0,8}},138}, {{{0,8}},74}, {{{0,9}},244},
    {{{80,7}},5}, {{{0,8}},86}, {{{0,8}},22}, {{{192,8}},0},
    {{{83,7}},51}, {{{0,8}},118}, {{{0,8}},54}, {{{0,9}},204},
    {{{81,7}},15}, {{{0,8}},102}, {{{0,8}},38}, {{{0,9}},172},
    {{{0,8}},6}, {{{0,8}},134}, {{{0,8}},70}, {{{0,9}},236},
    {{{80,7}},9}, {{{0,8}},94}, {{{0,8}},30}, {{{0,9}},156},
    {{{84,7}},99}, {{{0,8}},126}, {{{0,8}},62}, {{{0,9}},220},
    {{{82,7}},27}, {{{0,8}},110}, {{{0,8}},46}, {{{0,9}},188},
    {{{0,8}},14}, {{{0,8}},142}, {{{0,8}},78}, {{{0,9}},252},
    {{{96,7}},256}, {{{0,8}},81}, {{{0,8}},17}, {{{85,8}},131},
    {{{82,7}},31}, {{{0,8}},113}, {{{0,8}},49}, {{{0,9}},194},
    {{{80,7}},10}, {{{0,8}},97}, {{{0,8}},33}, {{{0,9}},162},
    {{{0,8}},1}, {{{0,8}},129}, {{{0,8}},65}, {{{0,9}},226},
    {{{80,7}},6}, {{{0,8}},89}, {{{0,8}},25}, {{{0,9}},146},
    {{{83,7}},59}, {{{0,8}},121}, {{{0,8}},57}, {{{0,9}},210},
    {{{81,7}},17}, {{{0,8}},105}, {{{0,8}},41}, {{{0,9}},178},
    {{{0,8}},9}, {{{0,8}},137}, {{{0,8}},73}, {{{0,9}},242},
    {{{80,7}},4}, {{{0,8}},85}, {{{0,8}},21}, {{{80,8}},258},
    {{{83,7}},43}, {{{0,8}},117}, {{{0,8}},53}, {{{0,9}},202},
    {{{81,7}},13}, {{{0,8}},101}, {{{0,8}},37}, {{{0,9}},170},
    {{{0,8}},5}, {{{0,8}},133}, {{{0,8}},69}, {{{0,9}},234},
    {{{80,7}},8}, {{{0,8}},93}, {{{0,8}},29}, {{{0,9}},154},
    {{{84,7}},83}, {{{0,8}},125}, {{{0,8}},61}, {{{0,9}},218},
    {{{82,7}},23}, {{{0,8}},109}, {{{0,8}},45}, {{{0,9}},186},
    {{{0,8}},13}, {{{0,8}},141}, {{{0,8}},77}, {{{0,9}},250},
    {{{80,7}},3}, {{{0,8}},83}, {{{0,8}},19}, {{{85,8}},195},
    {{{83,7}},35}, {{{0,8}},115}, {{{0,8}},51}, {{{0,9}},198},
    {{{81,7}},11}, {{{0,8}},99}, {{{0,8}},35}, {{{0,9}},166},
    {{{0,8}},3}, {{{0,8}},131}, {{{0,8}},67}, {{{0,9}},230},
    {{{80,7}},7}, {{{0,8}},91}, {{{0,8}},27}, {{{0,9}},150},
    {{{84,7}},67}, {{{0,8}},123}, {{{0,8}},59}, {{{0,9}},214},
    {{{82,7}},19}, {{{0,8}},107}, {{{0,8}},43}, {{{0,9}},182},
    {{{0,8}},11}, {{{0,8}},139}, {{{0,8}},75}, {{{0,9}},246},
    {{{80,7}},5}, {{{0,8}},87}, {{{0,8}},23}, {{{192,8}},0},
    {{{83,7}},51}, {{{0,8}},119}, {{{0,8}},55}, {{{0,9}},206},
    {{{81,7}},15}, {{{0,8}},103}, {{{0,8}},39}, {{{0,9}},174},
    {{{0,8}},7}, {{{0,8}},135}, {{{0,8}},71}, {{{0,9}},238},
    {{{80,7}},9}, {{{0,8}},95}, {{{0,8}},31}, {{{0,9}},158},
    {{{84,7}},99}, {{{0,8}},127}, {{{0,8}},63}, {{{0,9}},222},
    {{{82,7}},27}, {{{0,8}},111}, {{{0,8}},47}, {{{0,9}},190},
    {{{0,8}},15}, {{{0,8}},143}, {{{0,8}},79}, {{{0,9}},254},
    {{{96,7}},256}, {{{0,8}},80}, {{{0,8}},16}, {{{84,8}},115},
    {{{82,7}},31}, {{{0,8}},112}, {{{0,8}},48}, {{{0,9}},193},
    {{{80,7}},10}, {{{0,8}},96}, {{{0,8}},32}, {{{0,9}},161},
    {{{0,8}},0}, {{{0,8}},128}, {{{0,8}},64}, {{{0,9}},225},
    {{{80,7}},6}, {{{0,8}},88}, {{{0,8}},24}, {{{0,9}},145},
    {{{83,7}},59}, {{{0,8}},120}, {{{0,8}},56}, {{{0,9}},209},
    {{{81,7}},17}, {{{0,8}},104}, {{{0,8}},40}, {{{0,9}},177},
    {{{0,8}},8}, {{{0,8}},136}, {{{0,8}},72}, {{{0,9}},241},
    {{{80,7}},4}, {{{0,8}},84}, {{{0,8}},20}, {{{85,8}},227},
    {{{83,7}},43}, {{{0,8}},116}, {{{0,8}},52}, {{{0,9}},201},
    {{{81,7}},13}, {{{0,8}},100}, {{{0,8}},36}, {{{0,9}},169},
    {{{0,8}},4}, {{{0,8}},132}, {{{0,8}},68}, {{{0,9}},233},
    {{{80,7}},8}, {{{0,8}},92}, {{{0,8}},28}, {{{0,9}},153},
    {{{84,7}},83}, {{{0,8}},124}, {{{0,8}},60}, {{{0,9}},217},
    {{{82,7}},23}, {{{0,8}},108}, {{{0,8}},44}, {{{0,9}},185},
    {{{0,8}},12}, {{{0,8}},140}, {{{0,8}},76}, {{{0,9}},249},
    {{{80,7}},3}, {{{0,8}},82}, {{{0,8}},18}, {{{85,8}},163},
    {{{83,7}},35}, {{{0,8}},114}, {{{0,8}},50}, {{{0,9}},197},
    {{{81,7}},11}, {{{0,8}},98}, {{{0,8}},34}, {{{0,9}},165},
    {{{0,8}},2}, {{{0,8}},130}, {{{0,8}},66}, {{{0,9}},229},
    {{{80,7}},7}, {{{0,8}},90}, {{{0,8}},26}, {{{0,9}},149},
    {{{84,7}},67}, {{{0,8}},122}, {{{0,8}},58}, {{{0,9}},213},
    {{{82,7}},19}, {{{0,8}},106}, {{{0,8}},42}, {{{0,9}},181},
    {{{0,8}},10}, {{{0,8}},138}, {{{0,8}},74}, {{{0,9}},245},
    {{{80,7}},5}, {{{0,8}},86}, {{{0,8}},22}, {{{192,8}},0},
    {{{83,7}},51}, {{{0,8}},118}, {{{0,8}},54}, {{{0,9}},205},
    {{{81,7}},15}, {{{0,8}},102}, {{{0,8}},38}, {{{0,9}},173},
    {{{0,8}},6}, {{{0,8}},134}, {{{0,8}},70}, {{{0,9}},237},
    {{{80,7}},9}, {{{0,8}},94}, {{{0,8}},30}, {{{0,9}},157},
    {{{84,7}},99}, {{{0,8}},126}, {{{0,8}},62}, {{{0,9}},221},
    {{{82,7}},27}, {{{0,8}},110}, {{{0,8}},46}, {{{0,9}},189},
    {{{0,8}},14}, {{{0,8}},142}, {{{0,8}},78}, {{{0,9}},253},
    {{{96,7}},256}, {{{0,8}},81}, {{{0,8}},17}, {{{85,8}},131},
    {{{82,7}},31}, {{{0,8}},113}, {{{0,8}},49}, {{{0,9}},195},
    {{{80,7}},10}, {{{0,8}},97}, {{{0,8}},33}, {{{0,9}},163},
    {{{0,8}},1}, {{{0,8}},129}, {{{0,8}},65}, {{{0,9}},227},
    {{{80,7}},6}, {{{0,8}},89}, {{{0,8}},25}, {{{0,9}},147},
    {{{83,7}},59}, {{{0,8}},121}, {{{0,8}},57}, {{{0,9}},211},
    {{{81,7}},17}, {{{0,8}},105}, {{{0,8}},41}, {{{0,9}},179},
    {{{0,8}},9}, {{{0,8}},137}, {{{0,8}},73}, {{{0,9}},243},
    {{{80,7}},4}, {{{0,8}},85}, {{{0,8}},21}, {{{80,8}},258},
    {{{83,7}},43}, {{{0,8}},117}, {{{0,8}},53}, {{{0,9}},203},
    {{{81,7}},13}, {{{0,8}},101}, {{{0,8}},37}, {{{0,9}},171},
    {{{0,8}},5}, {{{0,8}},133}, {{{0,8}},69}, {{{0,9}},235},
    {{{80,7}},8}, {{{0,8}},93}, {{{0,8}},29}, {{{0,9}},155},
    {{{84,7}},83}, {{{0,8}},125}, {{{0,8}},61}, {{{0,9}},219},
    {{{82,7}},23}, {{{0,8}},109}, {{{0,8}},45}, {{{0,9}},187},
    {{{0,8}},13}, {{{0,8}},141}, {{{0,8}},77}, {{{0,9}},251},
    {{{80,7}},3}, {{{0,8}},83}, {{{0,8}},19}, {{{85,8}},195},
    {{{83,7}},35}, {{{0,8}},115}, {{{0,8}},51}, {{{0,9}},199},
    {{{81,7}},11}, {{{0,8}},99}, {{{0,8}},35}, {{{0,9}},167},
    {{{0,8}},3}, {{{0,8}},131}, {{{0,8}},67}, {{{0,9}},231},
    {{{80,7}},7}, {{{0,8}},91}, {{{0,8}},27}, {{{0,9}},151},
    {{{84,7}},67}, {{{0,8}},123}, {{{0,8}},59}, {{{0,9}},215},
    {{{82,7}},19}, {{{0,8}},107}, {{{0,8}},43}, {{{0,9}},183},
    {{{0,8}},11}, {{{0,8}},139}, {{{0,8}},75}, {{{0,9}},247},
    {{{80,7}},5}, {{{0,8}},87}, {{{0,8}},23}, {{{192,8}},0},
    {{{83,7}},51}, {{{0,8}},119}, {{{0,8}},55}, {{{0,9}},207},
    {{{81,7}},15}, {{{0,8}},103}, {{{0,8}},39}, {{{0,9}},175},
    {{{0,8}},7}, {{{0,8}},135}, {{{0,8}},71}, {{{0,9}},239},
    {{{80,7}},9}, {{{0,8}},95}, {{{0,8}},31}, {{{0,9}},159},
    {{{84,7}},99}, {{{0,8}},127}, {{{0,8}},63}, {{{0,9}},223},
    {{{82,7}},27}, {{{0,8}},111}, {{{0,8}},47}, {{{0,9}},191},
    {{{0,8}},15}, {{{0,8}},143}, {{{0,8}},79}, {{{0,9}},255}
  };
const inflate_huft fixed_td[] = {
    {{{80,5}},1}, {{{87,5}},257}, {{{83,5}},17}, {{{91,5}},4097},
    {{{81,5}},5}, {{{89,5}},1025}, {{{85,5}},65}, {{{93,5}},16385},
    {{{80,5}},3}, {{{88,5}},513}, {{{84,5}},33}, {{{92,5}},8193},
    {{{82,5}},9}, {{{90,5}},2049}, {{{86,5}},129}, {{{192,5}},24577},
    {{{80,5}},2}, {{{87,5}},385}, {{{83,5}},25}, {{{91,5}},6145},
    {{{81,5}},7}, {{{89,5}},1537}, {{{85,5}},97}, {{{93,5}},24577},
    {{{80,5}},4}, {{{88,5}},769}, {{{84,5}},49}, {{{92,5}},12289},
    {{{82,5}},13}, {{{90,5}},3073}, {{{86,5}},193}, {{{192,5}},24577}
  };

// copy as much as possible from the sliding window to the output area
int inflate_flush(inflate_blocks_statef *s,z_streamp z,int r)
{
	uInt n;
	Byte *p;
	Byte *q;

	if(0) OutputDebugString("inflate_flush..\r\n");
	// local copies of source and destination pointers 
	p = z->next_out;
	q = s->read;

	// compute number of bytes to copy as far as end of window 
	n = (uInt)((q <= s->write ? s->write : s->end) - q);
	if (n > z->avail_out) n = z->avail_out;
	if (n && r == Z_BUF_ERROR) r = Z_OK;

	// update counters
	z->avail_out -= n;
	z->total_out += n;

	// update check information 
	if (s->checkfn != Z_nullptr)
		z->adler = s->check = (*s->checkfn)(s->check, q, n);

	// copy as far as end of window 
	if (n!=0)          // check for n!=0 to avoid waking up CodeGuard
	{ 
		CopyMemory(p, q, n);
		p += n;
		q += n;
	}

	// see if more to copy at beginning of window
	if (q == s->end)
	{
		// wrap pointers 
		q = s->window;
		if (s->write == s->end)
			s->write = s->window;

		// compute bytes to copy 
		n = (uInt)(s->write - q);
		if (n > z->avail_out) n = z->avail_out;
		if (n && r == Z_BUF_ERROR) r = Z_OK;

		// update counters 
		z->avail_out -= n;
		z->total_out += n;

		// update check information 
		if (s->checkfn != Z_nullptr)
			z->adler = s->check = (*s->checkfn)(s->check, q, n);

		// copy
		CopyMemory(p, q, n);
		p += n;
		q += n;
	}

	// update pointers
	z->next_out = p;
	s->read = q;

	// done
	return r;
}


// simplify the use of the inflate_huft type with some defines
#define exop word.what.Exop
#define bits word.what.Bits

typedef enum {        // waiting for "i:"=input, "o:"=output, "x:"=nothing 
	START,    // x: set up for LEN 
	LEN,      // i: get length/literal/eob next 
	LENEXT,   // i: getting length extra (have base) 
	DIST,     // i: get distance next 
	DISTEXT,  // i: getting distance extra 
	COPY,     // o: copying bytes in window, waiting for space
	LIT,      // o: got literal, waiting for output space 
	WASH,     // o: got eob, possibly still output waiting 
	END,      // x: got eob and all data flushed 
	BADCODE}  // x: got error 
inflate_codes_mode;

// inflate codes private state
struct inflate_codes_state {

	// mode 
	inflate_codes_mode mode;      // current inflate_codes mode 

	// mode dependent information 
	uInt len;
	union {
		struct {
			const inflate_huft *tree;       // pointer into tree 
			uInt need;                // bits needed 
		} code;             // if LEN or DIST, where in tree 
		uInt lit;           // if LIT, literal 
		struct {
			uInt get;                 // bits to get for extra 
			uInt dist;                // distance back to copy from 
		} copy;             // if EXT or COPY, where and how much 
	} sub;                // submode

	// mode independent information 
	Byte lbits;           // ltree bits decoded per branch 
	Byte dbits;           // dtree bits decoder per branch 
	const inflate_huft *ltree;          // literal/length/eob tree
	const inflate_huft *dtree;          // distance tree

};


inflate_codes_statef *inflate_codes_new(uInt bl, uInt bd,const inflate_huft *tl,const inflate_huft *td,z_streamp z)
{
	inflate_codes_statef *c;
	if(0) OutputDebugString("inflate_codes_new..\r\n");

	if ((c = (inflate_codes_statef *)
		ZALLOC(z,1,sizeof(struct inflate_codes_state))) != Z_nullptr)
	{
		c->mode = START;
		c->lbits = (Byte)bl;
		c->dbits = (Byte)bd;
		c->ltree = tl;
		c->dtree = td;
	}
	return c;
}


int inflate_codes(inflate_blocks_statef *s, z_streamp z, int r)
{
	if(0) OutputDebugString("inflate_codes..\r\n");
	uInt j;               // temporary storage
	const inflate_huft *t;      // temporary pointer
	uInt e;               // extra bits or operation
	uLong b;              // bit buffer
	uInt k;               // bits in bit buffer
	Byte *p;             // input data pointer
	uInt n;               // bytes available there
	Byte *q;             // output window write pointer
	uInt m;               // bytes to end of window or read pointer
	Byte *f;             // pointer to copy strings from
	inflate_codes_statef *c = s->sub.decode.codes;  // codes state

	// copy input/output information to locals (s->bitb=b;s->bitk=k; z->avail_in=n;z->total_in+=(uLong)(p-z->next_in);z->next_in=p; s->write=q; macro restores)
	LOAD

	// process input and output based on current state
	for(;;) {
		switch (c->mode)
		{             // waiting for "i:"=input, "o:"=output, "x:"=nothing
		case START:         // x: set up for LEN
#ifndef SLOW
			if (m >= 258 && n >= 10)
			{
				s->bitb=b;s->bitk=k; z->avail_in=n;z->total_in+=(uLong)(p-z->next_in);z->next_in=p; s->write=q;
				r = inflate_fast(c->lbits, c->dbits, c->ltree, c->dtree, s, z);
				LOAD
				if (r != Z_OK)
				{
					c->mode = r == Z_STREAM_END ? WASH : BADCODE;
					break;
				}
			}
#endif // !SLOW
			c->sub.code.need = c->lbits;
			c->sub.code.tree = c->ltree;
			c->mode = LEN;
		case LEN:           // i: get length/literal/eob next
			j = c->sub.code.need;
			NEEDBITS(j)
				t = c->sub.code.tree + ((uInt)b & inflate_mask[j]);
			DUMPBITS(t->bits)
				e = (uInt)(t->exop);
			if (e == 0)               // literal 
			{
				c->sub.lit = t->base;
				////Tracevv((stderr, t->base >= 0x20 && t->base < 0x7f ? "inflate:         literal '%c'\n" :"inflate:         literal 0x%02x\n", t->base));
				c->mode = LIT;
				break;
			}
			if (e & 16)               // length 
			{
				c->sub.copy.get = e & 15;
				c->len = t->base;
				c->mode = LENEXT;
				break;
			}
			if ((e & 64) == 0)        // next table 
			{
				c->sub.code.need = e;
				c->sub.code.tree = t + t->base;
				break;
			}
			if (e & 32)               // end of block 
			{
				c->mode = WASH;
				break;
			}
			c->mode = BADCODE;        // invalid code 
			z->msg = (char*)"invalid literal/length code";
			r = Z_DATA_ERROR;
			LEAVE
		case LENEXT:        // i: getting length extra (have base) 
			j = c->sub.copy.get;
			NEEDBITS(j)
				c->len += (uInt)b & inflate_mask[j];
			DUMPBITS(j)
				c->sub.code.need = c->dbits;
			c->sub.code.tree = c->dtree;
			c->mode = DIST;
		case DIST:          // i: get distance next 
			j = c->sub.code.need;
			NEEDBITS(j)
				t = c->sub.code.tree + ((uInt)b & inflate_mask[j]);
			DUMPBITS(t->bits)
				e = (uInt)(t->exop);
			if (e & 16)               // distance 
			{
				c->sub.copy.get = e & 15;
				c->sub.copy.dist = t->base;
				c->mode = DISTEXT;
				break;
			}
			if ((e & 64) == 0)        // next table 
			{
				c->sub.code.need = e;
				c->sub.code.tree = t + t->base;
				break;
			}
			c->mode = BADCODE;        // invalid code 
			z->msg = (char*)"invalid distance code";
			r = Z_DATA_ERROR;
			LEAVE
		case DISTEXT:       // i: getting distance extra 
			j = c->sub.copy.get;
			NEEDBITS(j)
				c->sub.copy.dist += (uInt)b & inflate_mask[j];
			DUMPBITS(j)
				c->mode = COPY;
		case COPY:          // o: copying bytes in window, waiting for space 
			f = q - c->sub.copy.dist;
			if ((uInt)(q - s->window) < c->sub.copy.dist)
				f = s->end - (c->sub.copy.dist - (uInt)(q - s->window));
			while (c->len)
			{
				NEEDOUT
					OUTBYTE(*f++)
					if (f == s->end)
						f = s->window;
				c->len--;
			}
			c->mode = START;
			break;
		case LIT:           // o: got literal, waiting for output space 
			NEEDOUT
				OUTBYTE(c->sub.lit)
				c->mode = START;
			break;
		case WASH:          // o: got eob, possibly more output 
			if (k > 7)        // return unused byte, if any 
			{
				//if(k < 16)
				//	ExitProcess(1);// "inflate_codes grabbed too many bytes")
				k -= 8;
				n++;
				p--;            // can always return one 
			}
			FLUSH
				if (s->read != s->write)
					LEAVE
					c->mode = END;
		case END:
			r = Z_STREAM_END;
			LEAVE
		case BADCODE:       // x: got error
			r = Z_DATA_ERROR;
			LEAVE
		default:
			r = Z_STREAM_ERROR;
			LEAVE
		}
	}

}
void WINAPI inflate_codes_free(inflate_codes_statef *c,z_streamp z)
{ 
	if(0) OutputDebugString("inflate_codes_free..\r\n");
	ZFREE(z, c);
}



// infblock.c -- interpret and process block types to last block
// Copyright (C) 1995-1998 Mark Adler
// For conditions of distribution and use, see copyright notice in zlib.h

//struct inflate_codes_state {int dummy;}; // for buggy compilers 



// Table for deflate from PKZIP's appnote.txt.
const uInt border[] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};


void inflate_blocks_reset(inflate_blocks_statef *s, z_streamp z, uLong *c)
{
	if(0) OutputDebugString("inflate_blocks_reset..\r\n");
	if (c != Z_nullptr)
		*c = s->check;
	if (s->mode == BTREE || s->mode == DTREE)
		ZFREE(z, s->sub.trees.blens);
	if (s->mode == CODES) 
	{
		inflate_codes_free(s->sub.decode.codes, z);
	}
	s->mode = TYPE;
	s->bitk = 0;
	s->bitb = 0;
	s->read = s->write = s->window;
	if (s->checkfn != Z_nullptr)
		z->adler = s->check = (*s->checkfn)(0L, (const Byte *)Z_nullptr, 0);
}


inflate_blocks_statef *inflate_blocks_new(z_streamp z, check_func c, uInt w)
{
	if(0) OutputDebugString("inflate_blocks_new..\r\n");
	inflate_blocks_statef *s;

	if ((s = (inflate_blocks_statef *)ZALLOC(z,1,sizeof(struct inflate_blocks_state))) == Z_nullptr)
		return s;
	if ((s->hufts =	(inflate_huft *)ZALLOC(z, sizeof(inflate_huft), MANY)) == Z_nullptr)
	{
		ZFREE(z, s);
		return Z_nullptr;
	}
	if ((s->window = (Byte *)ZALLOC(z, 1, w)) == Z_nullptr)
	{
		ZFREE(z, s->hufts);
		ZFREE(z, s);
		return Z_nullptr;
	}
	s->end = s->window + w;
	s->checkfn = c;
	s->mode = TYPE;
	inflate_blocks_reset(s, z, Z_nullptr);
	return s;
}

int inflate_blocks(inflate_blocks_statef *s, z_streamp z, int r)
{
	if(0) OutputDebugString("inflate_blocks..\r\n");
	uInt t;               // temporary storage
	uLong b;              // bit buffer
	uInt k;               // bits in bit buffer
	Byte *p;             // input data pointer
	uInt n;               // bytes available there
	Byte *q;             // output window write pointer
	uInt m;               // bytes to end of window or read pointer 

	// copy input/output information to locals (s->bitb=b;s->bitk=k; z->avail_in=n;z->total_in+=(uLong)(p-z->next_in);z->next_in=p; s->write=q; macro restores) 

	LOAD
	// process input based on current state 
	for(;;) 
	{
		switch (s->mode)
		{
		case TYPE:
			NEEDBITS(3)
				t = (uInt)b & 7;
			s->last = t & 1;
			switch (t >> 1)
			{
			case 0:                         // stored 
				DUMPBITS(3)
					t = k & 7;                    // go to byte boundary 
				DUMPBITS(t)
					s->mode = LENS;               // get length of stored block
				break;
			case 1:                         // fixed 
				{
					uInt bl, bd;
					const inflate_huft *tl, *td;

					inflate_trees_fixed(&bl, &bd, &tl, &td, z);
					s->sub.decode.codes = inflate_codes_new(bl, bd, tl, td, z);
					if (s->sub.decode.codes == Z_nullptr)
					{
						r = Z_MEM_ERROR;
						LEAVE
					}
				}
				DUMPBITS(3)
					s->mode = CODES;
				break;
			case 2:                         // dynamic 
				DUMPBITS(3)
					s->mode = TABLE;
				break;
			case 3:                         // illegal
				DUMPBITS(3)
					s->mode = BAD;
				z->msg = (char*)"invalid block type";
				r = Z_DATA_ERROR;
				LEAVE
			}
			break;
		case LENS:
			NEEDBITS(32)
				if ((((~b) >> 16) & 0xffff) != (b & 0xffff))
				{
					s->mode = BAD;
					z->msg = (char*)"invalid stored block lengths";
					r = Z_DATA_ERROR;
					LEAVE
				}
				s->sub.left = (uInt)b & 0xffff;
				b = k = 0;                      // dump bits 
				s->mode = s->sub.left ? STORED : (s->last ? DRY : TYPE);
				break;
		case STORED:
			if (n == 0)
				LEAVE
				NEEDOUT
				t = s->sub.left;
			if (t > n) t = n;
			if (t > m) t = m;
			CopyMemory(q, p, t);
			p += t;  n -= t;
			q += t;  m -= t;
			if ((s->sub.left -= t) != 0)
				break;
			s->mode = s->last ? DRY : TYPE;
			break;
		case TABLE:
			NEEDBITS(14)
				s->sub.trees.table = t = (uInt)b & 0x3fff;
			// remove this section to workaround bug in pkzip
			if ((t & 0x1f) > 29 || ((t >> 5) & 0x1f) > 29)
			{
				s->mode = BAD;
				z->msg = (char*)"too many length or distance symbols";
				r = Z_DATA_ERROR;
				LEAVE
			}
			// end remove
			t = 258 + (t & 0x1f) + ((t >> 5) & 0x1f);
			if ((s->sub.trees.blens = (uInt*)ZALLOC(z, t, sizeof(uInt))) == Z_nullptr)
			{
				r = Z_MEM_ERROR;
				LEAVE
			}
			DUMPBITS(14)
				s->sub.trees.index = 0;
			s->mode = BTREE;
		case BTREE:
			while (s->sub.trees.index < 4 + (s->sub.trees.table >> 10))
			{
				NEEDBITS(3)
					s->sub.trees.blens[border[s->sub.trees.index++]] = (uInt)b & 7;
				DUMPBITS(3)
			}
			while (s->sub.trees.index < 19)
				s->sub.trees.blens[border[s->sub.trees.index++]] = 0;
			s->sub.trees.bb = 7;
			t = inflate_trees_bits(s->sub.trees.blens, &s->sub.trees.bb,&s->sub.trees.tb, s->hufts, z);
			if (t != Z_OK)
			{
				ZFREE(z, s->sub.trees.blens);
				r = t;
				if (r == Z_DATA_ERROR)
					s->mode = BAD;
				LEAVE
			}
			s->sub.trees.index = 0;
			s->mode = DTREE;
		case DTREE:
			while (t = s->sub.trees.table,
				s->sub.trees.index < 258 + (t & 0x1f) + ((t >> 5) & 0x1f))
			{
				inflate_huft *h;
				uInt i, j, c;

				t = s->sub.trees.bb;
				NEEDBITS(t)
					h = s->sub.trees.tb + ((uInt)b & inflate_mask[t]);
				t = h->bits;
				c = h->base;
				if (c < 16)
				{
					DUMPBITS(t)
						s->sub.trees.blens[s->sub.trees.index++] = c;
				}
				else // c == 16..18 
				{
					i = c == 18 ? 7 : c - 14;
					j = c == 18 ? 11 : 3;
					NEEDBITS(t + i)
						DUMPBITS(t)
						j += (uInt)b & inflate_mask[i];
					DUMPBITS(i)
						i = s->sub.trees.index;
					t = s->sub.trees.table;
					if (i + j > 258 + (t & 0x1f) + ((t >> 5) & 0x1f) ||
						(c == 16 && i < 1))
					{
						ZFREE(z, s->sub.trees.blens);
						s->mode = BAD;
						z->msg = (char*)"invalid bit length repeat";
						r = Z_DATA_ERROR;
						LEAVE
					}
					c = c == 16 ? s->sub.trees.blens[i - 1] : 0;
					do {
						s->sub.trees.blens[i++] = c;
					} while (--j);
					s->sub.trees.index = i;
				}
			}
			s->sub.trees.tb = Z_nullptr;
			{
				uInt bl, bd;
				inflate_huft *tl, *td;
				inflate_codes_statef *c;

				bl = 9;         // must be <= 9 for lookahead assumptions 
				bd = 6;         // must be <= 9 for lookahead assumptions
				t = s->sub.trees.table;
				t = inflate_trees_dynamic(257 + (t & 0x1f), 1 + ((t >> 5) & 0x1f),
					s->sub.trees.blens, &bl, &bd, &tl, &td,
					s->hufts, z);
				ZFREE(z, s->sub.trees.blens);
				if (t != Z_OK)
				{
					if (t == (uInt)Z_DATA_ERROR)
						s->mode = BAD;
					r = t;
					LEAVE
				}
				if ((c = inflate_codes_new(bl, bd, tl, td, z)) == Z_nullptr)
				{
					r = Z_MEM_ERROR;
					LEAVE
				}
				s->sub.decode.codes = c;
			}
			s->mode = CODES;
		case CODES:
			s->bitb=b;s->bitk=k; z->avail_in=n;z->total_in+=(uLong)(p-z->next_in);z->next_in=p; s->write=q;
			if ((r = inflate_codes(s, z, r)) != Z_STREAM_END)
				return inflate_flush(s, z, r);
			r = Z_OK;
			inflate_codes_free(s->sub.decode.codes, z);
			LOAD
			if (!s->last)
			{
				s->mode = TYPE;
				break;
			}
			s->mode = DRY;
		case DRY:
			FLUSH
				if (s->read != s->write)
					LEAVE
					s->mode = DONE;
		case DONE:
			r = Z_STREAM_END;
			LEAVE
		case BAD:
			r = Z_DATA_ERROR;
			LEAVE
		default:
			r = Z_STREAM_ERROR;
			LEAVE
		}
	}
}

int inflate_blocks_free(inflate_blocks_statef *s, z_streamp z)
{
	if(0) OutputDebugString("inflate_blocks_free..\r\n");
	inflate_blocks_reset(s, z, Z_nullptr);
	ZFREE(z, s->window);
	ZFREE(z, s->hufts);
	ZFREE(z, s);
	return Z_OK;
}

const uInt cplens[31] = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31,35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0, 0};
const uInt cplext[31] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2,3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0, 112, 112}; // 112==invalid
const uInt cpdist[30] = {1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193,257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145,8193, 12289, 16385, 24577};
const uInt cpdext[30] = {0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6,7, 7, 8, 8, 9, 9, 10, 10, 11, 11,12, 12, 13, 13};


// If BMAX needs to be larger than 16, then h and x[] should be uLong. 
#define BMAX 15         // maximum bit length of any code

int huft_build(uInt *b,uInt n,uInt s,const uInt *d,const uInt *e,inflate_huft * *t,uInt *m,inflate_huft *hp,uInt *hn,uInt *v)
{
	if(0) OutputDebugString("huft_build..\r\n");
	uInt a;                       // counter for codes of length k
	uInt c[BMAX+1];               // bit length count table
	uInt f;                       // i repeats in table every f entries 
	int g;                        // maximum code length 
	int h;                        // table level 
	register uInt i;              // counter, current code 
	register uInt j;              // counter
	register int k;               // number of bits in current code 
	int l;                        // bits per table (returned in m) 
	uInt mask;                    // (1 << w) - 1, to avoid cc -O bug on HP 
	register uInt *p;            // pointer into c[], b[], or v[]
	inflate_huft *q;              // points to current table 
	struct inflate_huft_s r;      // table entry for structure assignment 
	inflate_huft *u[BMAX];        // table stack 
	register int w;               // bits before this table == (l * h) 
	uInt x[BMAX+1];               // bit offsets, then code stack 
	uInt *xp;                    // pointer into x 
	int y;                        // number of dummy codes added 
	uInt z;                       // number of entries in current table 

	// Generate counts for each bit length 
	p = c;
#define C0 *p++ = 0;
#define C2 C0 C0 C0 C0
#define C4 C2 C2 C2 C2
	C4; p;                          // clear c[]--assume BMAX+1 is 16
	p = b;  i = n;
	do {
		c[*p++]++;                  // assume all entries <= BMAX 
	} while (--i);
	if (c[0] == n)                // nullptr input--all zero length codes 
	{
		*t = (inflate_huft *)Z_nullptr;
		*m = 0;
		return Z_OK;
	}

	// Find minimum and maximum length, bound *m by those 
	l = *m;
	for (j = 1; j <= BMAX; j++)
		if (c[j])
			break;
	k = j;                        // minimum code length 
	if ((uInt)l < j)
		l = j;
	for (i = BMAX; i; i--)
		if (c[i])
			break;
	g = i;                        // maximum code length 
	if ((uInt)l > i)
		l = i;
	*m = l;


	// Adjust last length count to fill out codes, if needed 
	for (y = 1 << j; j < i; j++, y <<= 1)
		if ((y -= c[j]) < 0)
			return Z_DATA_ERROR;
	if ((y -= c[i]) < 0)
		return Z_DATA_ERROR;
	c[i] += y;


	// Generate starting offsets into the value table for each length 
	x[1] = j = 0;
	p = c + 1;  xp = x + 2;
	while (--i) {                 // note that i == g from above 
		*xp++ = (j += *p++);
	}


	// Make a table of values in order of bit lengths 
	p = b;  i = 0;
	do {
		if ((j = *p++) != 0)
			v[x[j]++] = i;
	} while (++i < n);
	n = x[g];                     // set n to length of v 


	// Generate the Huffman codes and for each, make the table entries 
	x[0] = i = 0;                 // first Huffman code is zero 
	p = v;                        // grab values in bit order 
	h = -1;                       // no tables yet--level -1 
	w = -l;                       // bits decoded == (l * h) 
	u[0] = (inflate_huft *)Z_nullptr;        // just to keep compilers happy 
	q = (inflate_huft *)Z_nullptr;   // ditto 
	z = 0;                        // ditto 

	// go through the bit lengths (k already is bits in shortest code) 
	for (; k <= g; k++)
	{
		a = c[k];
		while (a--)
		{
			// here i is the Huffman code of length k bits for value *p 
			// make tables up to required level 
			while (k > w + l)
			{
				h++;
				w += l;                 // previous table always l bits 

				// compute minimum size table less than or equal to l bits
				z = g - w;
				z = z > (uInt)l ? l : z;        // table size upper limit 
				if ((f = 1 << (j = k - w)) > a + 1)     // try a k-w bit table 
				{                       // too few codes for k-w bit table 
					f -= a + 1;           // deduct codes from patterns left 
					xp = c + k;
					if (j < z)
						while (++j < z)     // try smaller tables up to z bits 
						{
							if ((f <<= 1) <= *++xp)
								break;          // enough codes to use up j bits 
							f -= *xp;         // else deduct codes from patterns
						}
				}
				z = 1 << j;             // table entries for j-bit table 

				// allocate new table 
				if (*hn + z > MANY)     // (note: doesn't matter for fixed) 
					return Z_MEM_ERROR;   // not enough memory 
				u[h] = q = hp + *hn;
				*hn += z;

				// connect to last table, if there is one 
				if (h)
				{
					x[h] = i;             // save pattern for backing up
					r.bits = (Byte)l;     // bits to dump before this table 
					r.exop = (Byte)j;     // bits in this table 
					j = i >> (w - l);
					r.base = (uInt)(q - u[h-1] - j);   // offset to this table 
					u[h-1][j] = r;        // connect to last table 
				}
				else
					*t = q;               // first table is returned result 
			}

			// set up table entry in r 
			r.bits = (Byte)(k - w);
			if (p >= v + n)
				r.exop = 128 + 64;      // out of values--invalid code 
			else if (*p < s)
			{
				r.exop = (Byte)(*p < 256 ? 0 : 32 + 64);     // 256 is end-of-block 
				r.base = *p++;          // simple code is just the value 
			}
			else
			{
				r.exop = (Byte)(e[*p - s] + 16 + 64);// non-simple--look up in lists 
				r.base = d[*p++ - s];
			}

			// fill code-like entries with r
			f = 1 << (k - w);
			for (j = i >> w; j < z; j += f)
				q[j] = r;

			// backwards increment the k-bit code i 
			for (j = 1 << (k - 1); i & j; j >>= 1)
				i ^= j;
			i ^= j;

			// backup over finished tables 
			mask = (1 << w) - 1;      // needed on HP, cc -O bug 
			while ((i & mask) != x[h])
			{
				h--;                    // don't need to update q
				w -= l;
				mask = (1 << w) - 1;
			}
		}
	}


	// Return Z_BUF_ERROR if we were given an incomplete table 
	return y != 0 && g != 1 ? Z_BUF_ERROR : Z_OK;
}


int inflate_trees_bits(uInt *c,uInt *bb,inflate_huft * *tb,inflate_huft *hp,z_streamp z)            // for messages
{
	if(0) OutputDebugString("inflate_trees_bits..\r\n");
	int r;
	uInt hn = 0;          // hufts used in space 
	uInt *v;             // work area for huft_build 

	if ((v = (uInt*)ZALLOC(z, 19, sizeof(uInt))) == Z_nullptr)
		return Z_MEM_ERROR;
	r = huft_build(c, 19, 19, (uInt*)Z_nullptr, (uInt*)Z_nullptr,
		tb, bb, hp, &hn, v);
	if (r == Z_DATA_ERROR)
		z->msg = (char*)"oversubscribed dynamic bit lengths tree";
	else if (r == Z_BUF_ERROR || *bb == 0)
	{
		z->msg = (char*)"incomplete dynamic bit lengths tree";
		r = Z_DATA_ERROR;
	}
	ZFREE(z, v);
	return r;
}

int inflate_trees_dynamic(uInt nl,uInt nd,uInt *c,uInt *bl,uInt *bd,inflate_huft * *tl,inflate_huft * *td,inflate_huft *hp,z_streamp z)            // for messages
{
	if(0) OutputDebugString("inflate_trees_dynamic..\r\n");
	int r;
	uInt hn = 0;          // hufts used in space 
	uInt *v;             // work area for huft_build 

	// allocate work area 
	if ((v = (uInt*)ZALLOC(z, 288, sizeof(uInt))) == Z_nullptr)
		return Z_MEM_ERROR;

	// build literal/length tree 
	r = huft_build(c, nl, 257, cplens, cplext, tl, bl, hp, &hn, v);
	if (r != Z_OK || *bl == 0)
	{
		if (r == Z_DATA_ERROR)
			z->msg = (char*)"oversubscribed literal/length tree";
		else if (r != Z_MEM_ERROR)
		{
			z->msg = (char*)"incomplete literal/length tree";
			r = Z_DATA_ERROR;
		}
		ZFREE(z, v);
		return r;
	}

	// build distance tree 
	r = huft_build(c + nl, nd, 0, cpdist, cpdext, td, bd, hp, &hn, v);
	if (r != Z_OK || (*bd == 0 && nl > 257))
	{
		if (r == Z_DATA_ERROR)
			z->msg = (char*)"oversubscribed distance tree";
		else if (r == Z_BUF_ERROR) {
			z->msg = (char*)"incomplete distance tree";
			r = Z_DATA_ERROR;
		}
		else if (r != Z_MEM_ERROR)
		{
			z->msg = (char*)"empty distance tree with lengths";
			r = Z_DATA_ERROR;
		}
		ZFREE(z, v);
		return r;
	}

	// done 
	ZFREE(z, v);
	return Z_OK;
}





int inflate_trees_fixed(uInt *bl,               // literal desired/actual bit depth
						uInt *bd,               // distance desired/actual bit depth
						const inflate_huft * * tl,     // literal/length tree result
						const inflate_huft * *td,     // distance tree result
						z_streamp )             // for memory allocation
{
	*bl = fixed_bl;
	*bd = fixed_bd;
	*tl = fixed_tl;
	*td = fixed_td;
	if(0) OutputDebugString("inflate_trees_fixed..\r\n");
	return Z_OK;
}


// inffast.c -- process literals and length/distance pairs fast
// Copyright (C) 1995-1998 Mark Adler
// For conditions of distribution and use, see copyright notice in zlib.h
//


//struct inflate_codes_state {int dummy;}; // for buggy compilers 


// macros for bit input with no checking and for returning unused bytes 
#define GRABBITS(j) {while(k<(j)){b|=((uLong)NEXTBYTE)<<k;k+=8;}}
#define UNGRAB {c=z->avail_in-n;c=(k>>3)<c?k>>3:c;n+=c;p-=c;k-=c<<3;}

// Called with number of bytes left to write in window at least 258
// (the maximum string length) and number of input bytes available
// at least ten.  The ten bytes are six bytes for the longest length/
// distance pair plus four bytes for overloading the bit buffer. 

int inflate_fast(uInt bl, uInt bd,const inflate_huft *tl,const inflate_huft *td, inflate_blocks_statef *s,z_streamp z)
{
	if(0) OutputDebugString("inflate_fast..\r\n");
	const inflate_huft *t;      // temporary pointer 
	uInt e;               // extra bits or operation 
	uLong b;              // bit buffer 
	uInt k;               // bits in bit buffer 
	Byte *p;             // input data pointer 
	uInt n;               // bytes available there 
	Byte *q;             // output window write pointer 
	uInt m;               // bytes to end of window or read pointer 
	uInt ml;              // mask for literal/length tree
	uInt md;              // mask for distance tree 
	uInt c;               // bytes to copy 
	uInt d;               // distance back to copy from 
	Byte *r;             // copy source pointer 

	// load input, output, bit values 
	LOAD

	// initialize masks 
	ml = inflate_mask[bl];
	md = inflate_mask[bd];

	// do until not enough input or output space for fast loop 
	do {                          // assume called with m >= 258 && n >= 10 
		// get literal/length code 
		GRABBITS(20)                // max bits for literal/length code 
			if ((e = (t = tl + ((uInt)b & ml))->exop) == 0)
			{
				DUMPBITS(t->bits)
					*q++ = (Byte)t->base;
				m--;
				continue;
			}
			for (;;) {
				DUMPBITS(t->bits)
					if (e & 16)
					{
						// get extra bits for length 
						e &= 15;
						c = t->base + ((uInt)b & inflate_mask[e]);
						DUMPBITS(e)

							// decode distance base of block to copy 
							GRABBITS(15);           // max bits for distance code 
						e = (t = td + ((uInt)b & md))->exop;
						for (;;) {
							DUMPBITS(t->bits)
								if (e & 16)
								{
									// get extra bits to add to distance base 
									e &= 15;
									GRABBITS(e)         // get extra bits (up to 13) 
										d = t->base + ((uInt)b & inflate_mask[e]);
									DUMPBITS(e)

										// do the copy 
										m -= c;
									if ((uInt)(q - s->window) >= d)     // offset before dest 
									{                                   //  just copy 
										r = q - d;
										*q++ = *r++;  c--;        // minimum count is three, 
										*q++ = *r++;  c--;        //  so unroll loop a little 
									}
									else                        // else offset after destination 
									{
										e = d - (uInt)(q - s->window); // bytes from offset to end 
										r = s->end - e;           // pointer to offset 
										if (c > e)                // if source crosses, 
										{
											c -= e;                 // copy to end of window 
											do {
												*q++ = *r++;
											} while (--e);
											r = s->window;          // copy rest from start of window 
										}
									}
									do {                        // copy all or what's left 
										*q++ = *r++;
									} while (--c);
									break;
								}
								else if ((e & 64) == 0)
								{
									t += t->base;
									e = (t += ((uInt)b & inflate_mask[e]))->exop;
								}
								else
								{
									z->msg = (char*)"invalid distance code";
									UNGRAB
										s->bitb=b;s->bitk=k; z->avail_in=n;z->total_in+=(uLong)(p-z->next_in);z->next_in=p; s->write=q;
									return Z_DATA_ERROR;
								}
						};
						break;
					}
					if ((e & 64) == 0)
					{
						t += t->base;
						if ((e = (t += ((uInt)b & inflate_mask[e]))->exop) == 0)
						{
							DUMPBITS(t->bits)
								*q++ = (Byte)t->base;
							m--;
							break;
						}
					}
					else if (e & 32)
					{
						UNGRAB
							s->bitb=b;s->bitk=k; z->avail_in=n;z->total_in+=(uLong)(p-z->next_in);z->next_in=p; s->write=q;
						return Z_STREAM_END;
					}
					else
					{
						z->msg = (char*)"invalid literal/length code";
						UNGRAB
							s->bitb=b;s->bitk=k; z->avail_in=n;z->total_in+=(uLong)(p-z->next_in);z->next_in=p; s->write=q;
						return Z_DATA_ERROR;
					}
			};
	} while (m >= 258 && n >= 10);

	// not enough input or output--restore pointers and return
	UNGRAB
		s->bitb=b;s->bitk=k; z->avail_in=n;z->total_in+=(uLong)(p-z->next_in);z->next_in=p; s->write=q;
	return Z_OK;
}


// Table of CRC-32's of all single-byte values (made by make_crc_table)
const uLong crc_table[256] = {0L};

const uLong * get_crc_table()
{ 
	if(0) OutputDebugString("get_crc_table..\r\n");
	return (const uLong *)crc_table;
}

#define CRC_DO1(buf) crc = crc_table[((int)crc ^ (*buf++)) & 0xff] ^ (crc >> 8);
#define CRC_DO2(buf)  CRC_DO1(buf); CRC_DO1(buf);
#define CRC_DO4(buf)  CRC_DO2(buf); CRC_DO2(buf);
#define CRC_DO8(buf)  CRC_DO4(buf); CRC_DO4(buf);

uLong ucrc32(uLong crc, const Byte *buf, uInt len)
{ 
	if(0) OutputDebugString("ucrc32..\r\n");
	if (buf == Z_nullptr) return 0L;
	crc = crc ^ 0xffffffffL;
	while (len >= 8)  {CRC_DO8(buf); len -= 8;}
	if (len) do {CRC_DO1(buf);} while (--len);
	return crc ^ 0xffffffffL;
}


// adler32.c -- compute the Adler-32 checksum of a data stream
// Copyright (C) 1995-1998 Mark Adler
// For conditions of distribution and use, see copyright notice in zlib.h

// @(#) $Id$


#define BASE 65521L // largest prime smaller than 65536
#define NMAX 5552
// NMAX is the largest n such that 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1

#define AD_DO1(buf,i)  {s1 += buf[i]; s2 += s1;}
#define AD_DO2(buf,i)  AD_DO1(buf,i); AD_DO1(buf,i+1);
#define AD_DO4(buf,i)  AD_DO2(buf,i); AD_DO2(buf,i+2);
#define AD_DO8(buf,i)  AD_DO4(buf,i); AD_DO4(buf,i+4);
#define AD_DO16(buf)   AD_DO8(buf,0); AD_DO8(buf,8);

// =========================================================================
uLong adler32(uLong adler, const Byte *buf, uInt len)
{
	if(0) OutputDebugString("adler32..\r\n");
	unsigned long s1 = adler & 0xffff;
	unsigned long s2 = (adler >> 16) & 0xffff;
	int k;

	if (buf == Z_nullptr) return 1L;

	while (len > 0) {
		k = len < NMAX ? len : NMAX;
		len -= k;
		while (k >= 16) {
			AD_DO16(buf);
			buf += 16;
			k -= 16;
		}
		if (k != 0) do {
			s1 += *buf++;
			s2 += s1;
		} while (--k);
		s1 %= BASE;
		s2 %= BASE;
	}
	return (s2 << 16) | s1;
}

//const char * zlibVersion()
//{
//	return ZLIB_VERSION;
//}

// exported to allow conversion of error code to string for compress() and
// uncompress()
const char * zError(int err)
{ 
	if(0) OutputDebugString("zError..\r\n");
	return ERR_MSG(err);
}

voidpf zcalloc (voidpf opaque, unsigned items, unsigned size)
{
	if(0) OutputDebugString("zcalloc..\r\n");
	if (opaque) items += size - size; // make compiler happy
	///////????return (voidpf)calloc(items, size);
	return (voidpf)zmalloc(items*size);
}

void  zcfree (voidpf opaque, voidpf ptr)
{
	if(0) OutputDebugString("zcfree..\r\n");
	zfree(ptr);
	if (opaque) return; // make compiler happy
}

typedef enum {
	IM_METHOD,   // waiting for method byte
	IM_FLAG,     // waiting for flag byte
	IM_DICT4,    // four dictionary check bytes to go
	IM_DICT3,    // three dictionary check bytes to go
	IM_DICT2,    // two dictionary check bytes to go
	IM_DICT1,    // one dictionary check byte to go
	IM_DICT0,    // waiting for inflateSetDictionary
	IM_BLOCKS,   // decompressing blocks
	IM_CHECK4,   // four check bytes to go
	IM_CHECK3,   // three check bytes to go
	IM_CHECK2,   // two check bytes to go
	IM_CHECK1,   // one check byte to go
	IM_DONE,     // finished check, done
	IM_BAD}      // got an error--stay here
inflate_mode;

// inflate private state
struct internal_state {

	// mode
	inflate_mode  mode;   // current inflate mode

	// mode dependent information
	union {
		uInt method;        // if IM_FLAGS, method byte
		struct {
			uLong was;                // computed check value
			uLong need;               // stream check value
		} check;            // if CHECK, check values to compare
		uInt marker;        // if IM_BAD, inflateSync's marker bytes count
	} sub;        // submode

	// mode independent information
	int  nowrap;          // flag for no wrapper
	uInt wbits;           // log2(window size)  (8..15, defaults to 15)
	inflate_blocks_statef	*blocks;            // current inflate_blocks state
};

int inflateReset(z_streamp z)
{
	if(0) OutputDebugString("inflateReset..\r\n");
	if (z == Z_nullptr || z->state == Z_nullptr)
		return Z_STREAM_ERROR;
	z->total_in = z->total_out = 0;
	z->msg = Z_nullptr;
	z->state->mode = z->state->nowrap ? IM_BLOCKS : IM_METHOD;
	inflate_blocks_reset(z->state->blocks, z, Z_nullptr);
	return Z_OK;
}

int inflateEnd(z_streamp z)
{
	if(0) OutputDebugString("inflateEnd..\r\n");
	if (z == Z_nullptr || z->state == Z_nullptr || z->zfree == Z_nullptr)
		return Z_STREAM_ERROR;
	if (z->state->blocks != Z_nullptr)
		inflate_blocks_free(z->state->blocks, z);
	ZFREE(z, z->state);
	z->state = Z_nullptr;
	return Z_OK;
}


int inflateInit2(z_streamp z)
{ 
	if(0) OutputDebugString("inflateInit2..\r\n");
	const char *version = ZLIB_VERSION; 
	int stream_size = sizeof(z_stream);
	if (version == Z_nullptr || version[0] != ZLIB_VERSION[0] || stream_size != sizeof(z_stream)) 
		return Z_VERSION_ERROR;

	int w = -15; // MAX_WBITS: 32K LZ77 window.


	// initialize state
	if (z == Z_nullptr) return Z_STREAM_ERROR;
	z->msg = Z_nullptr;
	if (z->zalloc == Z_nullptr)
	{
		z->zalloc = zcalloc;
		z->opaque = (voidpf)0;
	}
	if (z->zfree == Z_nullptr) z->zfree = zcfree;
	if ((z->state = (struct internal_state *)
		ZALLOC(z,1,sizeof(struct internal_state))) == Z_nullptr)
		return Z_MEM_ERROR;
	z->state->blocks = Z_nullptr;

	// handle undocumented nowrap option (no zlib header or check)
	z->state->nowrap = 0;
	if (w < 0)
	{
		w = - w;
		z->state->nowrap = 1;
	}

	// set window size
	if (w < 8 || w > 15)
	{
		inflateEnd(z);
		return Z_STREAM_ERROR;
	}
	z->state->wbits = (uInt)w;

	// create inflate_blocks state
	if ((z->state->blocks =
		inflate_blocks_new(z, z->state->nowrap ? Z_nullptr : adler32, (uInt)1 << w))== Z_nullptr)
	{
		inflateEnd(z);
		return Z_MEM_ERROR;
	}

	// reset state 
	inflateReset(z);
	return Z_OK;
}
#define IM_NEEDBYTE {if(z->avail_in==0)return r;r=f;}
#define IM_NEXTBYTE (z->avail_in--,z->total_in++,*z->next_in++)

int inflate(z_streamp z, int f)
{
	if(0) OutputDebugString("inflate..\r\n");
	int r;
	uInt b;

	if (z == Z_nullptr || z->state == Z_nullptr || z->next_in == Z_nullptr)
		return Z_STREAM_ERROR;
	f = f == Z_FINISH ? Z_BUF_ERROR : Z_OK;
	r = Z_BUF_ERROR;
	for (;;) 
	{
		switch (z->state->mode)
		{
		case IM_METHOD:
			IM_NEEDBYTE
				if (((z->state->sub.method = IM_NEXTBYTE) & 0xf) != Z_DEFLATED)
				{
					z->state->mode = IM_BAD;
					z->msg = (char*)"unknown compression method";
					z->state->sub.marker = 5;       // can't try inflateSync
					break;
				}
				if ((z->state->sub.method >> 4) + 8 > z->state->wbits)
				{
					z->state->mode = IM_BAD;
					z->msg = (char*)"invalid window size";
					z->state->sub.marker = 5;       // can't try inflateSync
					break;
				}
				z->state->mode = IM_FLAG;
		case IM_FLAG:
			IM_NEEDBYTE
				b = IM_NEXTBYTE;
			if (((z->state->sub.method << 8) + b) % 31)
			{
				z->state->mode = IM_BAD;
				z->msg = (char*)"incorrect header check";
				z->state->sub.marker = 5;       // can't try inflateSync 
				break;
			}
			if (!(b & PRESET_DICT))
			{
				z->state->mode = IM_BLOCKS;
				break;
			}
			z->state->mode = IM_DICT4;
		case IM_DICT4:
			IM_NEEDBYTE
				z->state->sub.check.need = (uLong)IM_NEXTBYTE << 24;
			z->state->mode = IM_DICT3;
		case IM_DICT3:
			IM_NEEDBYTE
				z->state->sub.check.need += (uLong)IM_NEXTBYTE << 16;
			z->state->mode = IM_DICT2;
		case IM_DICT2:
			IM_NEEDBYTE
				z->state->sub.check.need += (uLong)IM_NEXTBYTE << 8;
			z->state->mode = IM_DICT1;
		case IM_DICT1:
			IM_NEEDBYTE; r;
			z->state->sub.check.need += (uLong)IM_NEXTBYTE;
			z->adler = z->state->sub.check.need;
			z->state->mode = IM_DICT0;
			return Z_NEED_DICT;
		case IM_DICT0:
			z->state->mode = IM_BAD;
			z->msg = (char*)"need dictionary";
			z->state->sub.marker = 0;       // can try inflateSync 
			return Z_STREAM_ERROR;
		case IM_BLOCKS:
			r = inflate_blocks(z->state->blocks, z, r);
			if (r == Z_DATA_ERROR)
			{
				z->state->mode = IM_BAD;
				z->state->sub.marker = 0;       // can try inflateSync 
				break;
			}
			if (r == Z_OK)
				r = f;
			if (r != Z_STREAM_END)
				return r;
			r = f;
			inflate_blocks_reset(z->state->blocks, z, &z->state->sub.check.was);
			if (z->state->nowrap)
			{
				z->state->mode = IM_DONE;
				break;
			}
			z->state->mode = IM_CHECK4;
		case IM_CHECK4:
			IM_NEEDBYTE
				z->state->sub.check.need = (uLong)IM_NEXTBYTE << 24;
			z->state->mode = IM_CHECK3;
		case IM_CHECK3:
			IM_NEEDBYTE
				z->state->sub.check.need += (uLong)IM_NEXTBYTE << 16;
			z->state->mode = IM_CHECK2;
		case IM_CHECK2:
			IM_NEEDBYTE
				z->state->sub.check.need += (uLong)IM_NEXTBYTE << 8;
			z->state->mode = IM_CHECK1;
		case IM_CHECK1:
			IM_NEEDBYTE
				z->state->sub.check.need += (uLong)IM_NEXTBYTE;

			if (z->state->sub.check.was != z->state->sub.check.need)
			{
				z->state->mode = IM_BAD;
				z->msg = (char*)"incorrect data check";
				z->state->sub.marker = 5;       // can't try inflateSync 
				break;
			}
			z->state->mode = IM_DONE;
		case IM_DONE:
			return Z_STREAM_END;
		case IM_BAD:
			return Z_DATA_ERROR;
		default:
			return Z_STREAM_ERROR;
		}
	}
}

#define UNZ_BUFSIZE (16384)
#define UNZ_MAXFILENAMEINZIP (256)
#define SIZECENTRALDIRITEM (0x2e)
#define SIZEZIPLOCALHEADER (0x1e)

const char unz_copyright[] = " unzip 0.15 Copyright 1998 Gilles Vollant ";

// unz_file_info_interntal contain internal info about a file in zipfile
typedef struct unz_file_info_internal_s
{
	uLong offset_curfile;// relative offset of local header 4 bytes
} unz_file_info_internal;


typedef struct
{ 
	bool is_handle; // either a handle or memory
	bool canseek;
	// for handles:
	HANDLE h; 
	bool herr; 
	unsigned long initial_offset;
	// for memory:
	void *buf; 
	unsigned int len,pos; // if it's a memory block
} LUFILE;


LUFILE *lufopen(void *z,unsigned int len,DWORD flags,ZRESULT *err)
{ 
	if(0) OutputDebugString("lufopen..\r\n");
	if (flags!=ZIP_HANDLE && flags!=ZIP_FILENAME && flags!=ZIP_MEMORY) 
	{
		*err=ZR_ARGS; 
		return nullptr;
	}
	//
	HANDLE h=0; bool canseek=false; *err=ZR_OK;
	if (flags==ZIP_HANDLE||flags==ZIP_FILENAME)
	{ 
		if (flags==ZIP_HANDLE)
		{ 
			HANDLE hf = z;

			BOOL res = DuplicateHandle(GetCurrentProcess(),hf,GetCurrentProcess(),&h,0,FALSE,DUPLICATE_SAME_ACCESS);

			if (!res) 
			{
				*err=ZR_NODUPH; 
				return nullptr;
			}
		}
		else
		{ 
			h = CreateFile((const TCHAR *)z, GENERIC_READ, FILE_SHARE_READ,nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

			if (h == INVALID_HANDLE_VALUE) 
			{
				*err = ZR_NOFILE; 
				return nullptr;
			}
		}
		DWORD type = GetFileType(h);
		canseek = (type==FILE_TYPE_DISK);
	}
	LUFILE *lf = new LUFILE;
	if (flags==ZIP_HANDLE||flags==ZIP_FILENAME)
	{ 
		lf->is_handle=true;
		lf->canseek=canseek;
		lf->h=h; lf->herr=false;
		lf->initial_offset=0;
		if (canseek) 
			lf->initial_offset = SetFilePointer(h,0,nullptr,FILE_CURRENT);
	}
	else
	{ 
		lf->is_handle=false;
		lf->canseek=true;
		lf->buf=z; 
		lf->len=len; 
		lf->pos=0; 
		lf->initial_offset=0;
	}
	*err=ZR_OK;
	return lf;
}


int lufclose(LUFILE *stream)
{ 
	if(0) OutputDebugString("lufclose..\r\n");
	if (stream==nullptr) 
		return UNZ_EOF;
	if (stream->is_handle) 
		CloseHandle(stream->h);
	delete stream;
	return 0;
}

int luferror(LUFILE *stream)
{ 
	if(0) OutputDebugString("luferror..\r\n");
	if (stream->is_handle && stream->herr) return 1;
	else return 0;
}

long int luftell(LUFILE *stream)
{ 
	if(0) OutputDebugString("luftell..\r\n");
	if (stream->is_handle && stream->canseek) 
		return SetFilePointer(stream->h,0,nullptr,FILE_CURRENT)-stream->initial_offset;
	else if (stream->is_handle) return 0;
	else return stream->pos;
}

int lufseek(LUFILE *stream, long offset, int whence)
{ 
	if(0) OutputDebugString("lufseek..\r\n");
	if (stream->is_handle && stream->canseek)
	{ 
		if (whence==SEEK_SET) 
			SetFilePointer(stream->h,stream->initial_offset+offset,0,FILE_BEGIN);
		else if (whence==SEEK_CUR) 
			SetFilePointer(stream->h,offset,nullptr,FILE_CURRENT);
		else if (whence==SEEK_END) 
			SetFilePointer(stream->h,offset,nullptr,FILE_END);
		else 
			return 19; // EINVAL
		return 0;
	}
	else if (stream->is_handle) 
		return 29; // ESPIPE
	else
	{
		if (whence==SEEK_SET) 
			stream->pos=offset;
		else if (whence==SEEK_CUR) 
			stream->pos+=offset;
		else if (whence==SEEK_END) 
			stream->pos=stream->len+offset;
		return 0;
	}
}

size_t lufread(void *ptr,size_t size,size_t n,LUFILE *stream)
{
	if(0) OutputDebugString("lufread..\r\n");
	unsigned int toread = (unsigned int)(size*n);
	if (stream->is_handle)
	{
		DWORD red; 
		BOOL res = ReadFile(stream->h,ptr,toread,&red,nullptr);
		if (!res) 
			stream->herr=true;
		return red/size;
	}
	if (stream->pos+toread > stream->len) 
		toread = stream->len-stream->pos;
	CopyMemory(ptr, (char*)stream->buf + stream->pos, toread);
	DWORD red = toread;
	stream->pos += red;
	return red/size;
}

// file_in_zip_read_info_s contain internal information about a file in zipfile,
//  when reading and decompress it
typedef struct
{
	char  *read_buffer;         // internal buffer for compressed data
	z_stream stream;            // zLib stream structure for inflate

	uLong pos_in_zipfile;       // position in byte on the zipfile, for fseek
	uLong stream_initialised;   // flag set if stream structure is initialised

	uLong offset_local_extrafield;// offset of the local extra field
	uInt  size_local_extrafield;// size of the local extra field
	uLong pos_local_extrafield;   // position in the local extra field in read

	uLong crc32;                // crc32 of all data uncompressed
	uLong crc32_wait;           // crc32 we must obtain after decompress all
	uLong rest_read_compressed; // number of byte to be decompressed
	uLong rest_read_uncompressed;//number of byte to be obtained after decomp
	LUFILE* file;                 // io structore of the zipfile
	uLong compression_method;   // compression method (0==store)
	uLong byte_before_the_zipfile;// byte before the zipfile, (>0 for sfx)
} file_in_zip_read_info_s;


// unz_s contain internal information about the zipfile
typedef struct
{
	LUFILE* file;               // io structore of the zipfile
	unz_global_info gi;         // public global information
	uLong byte_before_the_zipfile;// byte before the zipfile, (>0 for sfx)
	uLong num_file;             // number of the current file in the zipfile
	uLong pos_in_central_dir;   // pos of the current file in the central dir
	uLong current_file_ok;      // flag about the usability of the current file
	uLong central_pos;          // position of the beginning of the central dir

	uLong size_central_dir;     // size of the central directory
	uLong offset_central_dir;   // offset of start of central directory with respect to the starting disk number

	unz_file_info cur_file_info; // public info about the current file in zip
	unz_file_info_internal cur_file_info_internal; // private info about it
	file_in_zip_read_info_s* pfile_in_zip_read; // structure about the current file if we are decompressing it
} unz_s, *unzFile;

//  Read extra field from the current file (opened by unzOpenCurrentFile)
int unzlocal_getByte(LUFILE *fin,int *pi)
{ 
	if(0) OutputDebugString("unzlocal_getByte..\r\n");
	unsigned char c;
	int err = (int)lufread(&c, 1, 1, fin);
	if (err==1)
	{ 
		*pi = (int)c; 
		return UNZ_OK;
	}
	else
	{ 
		if (luferror(fin)) 
			return UNZ_ERRNO;
		else 
			return UNZ_EOF;
	}
}


// ===========================================================================
// Reads a long in LSB order from the given gz_stream. Sets
int unzlocal_getShort (LUFILE *fin,uLong *pX)
{
	if(0) OutputDebugString("unzlocal_getShort..\r\n");
	uLong x ;
	int i;
	int err;

	err = unzlocal_getByte(fin,&i);
	x = (uLong)i;

	if (err==UNZ_OK)
		err = unzlocal_getByte(fin,&i);
	x += ((uLong)i)<<8;

	if (err==UNZ_OK)
		*pX = x;
	else
		*pX = 0;
	return err;
}

int unzlocal_getLong (LUFILE *fin,uLong *pX)
{
	if(0) OutputDebugString("unzlocal_getLong..\r\n");
	uLong x ;
	int i;
	int err;

	err = unzlocal_getByte(fin,&i);
	x = (uLong)i;

	if (err==UNZ_OK)
		err = unzlocal_getByte(fin,&i);
	x += ((uLong)i)<<8;

	if (err==UNZ_OK)
		err = unzlocal_getByte(fin,&i);
	x += ((uLong)i)<<16;

	if (err==UNZ_OK)
		err = unzlocal_getByte(fin,&i);
	x += ((uLong)i)<<24;

	if (err==UNZ_OK)
		*pX = x;
	else
		*pX = 0;
	return err;
}


// My own strcmpi / strcasecmp 
int strcmpcasenosensitive_internal (const char* fileName1,const char *fileName2)
{
	if(0) OutputDebugString("strcmpcasenosensitive_internal..\r\n");
	for (;;)
	{
		char c1=*(fileName1++);
		char c2=*(fileName2++);
		if ((c1>='a') && (c1<='z'))
			c1 -= (char)0x20;
		if ((c2>='a') && (c2<='z'))
			c2 -= (char)0x20;
		if (c1=='\0')
			return ((c2=='\0') ? 0 : -1);
		if (c2=='\0')
			return 1;
		if (c1<c2)
			return -1;
		if (c1>c2)
			return 1;
	}
}

int unzStringFileNameCompare (const char*fileName1,const char*fileName2,int iCaseSensitivity)
{
	if(0) OutputDebugString("unzStringFileNameCompare..\r\n");
	if (iCaseSensitivity==1) 
		return lstrcmpA(fileName1,fileName2);
	else 
		return strcmpcasenosensitive_internal(fileName1,fileName2);
} 

#define BUFREADCOMMENT (0x400)


//  Locate the Central directory of a zipfile (at the end, just before
// the global comment)
uLong unzlocal_SearchCentralDir(LUFILE *fin)
{
	if(0) OutputDebugString("unzlocal_SearchCentralDir..\r\n");
	if (lufseek(fin,0,SEEK_END) != 0) 
		return 0;
	uLong uSizeFile = luftell(fin);

	uLong uMaxBack=0xffff; // maximum size of global comment
	if (uMaxBack>uSizeFile) 
		uMaxBack = uSizeFile;

	unsigned char *buf = (unsigned char*)zmalloc(BUFREADCOMMENT+4);
	if (buf==nullptr) return 0;
	uLong uPosFound=0;

	uLong uBackRead = 4;
	while (uBackRead<uMaxBack)
	{ 
		uLong uReadSize,uReadPos ;
		int i;
		if (uBackRead+BUFREADCOMMENT>uMaxBack) 
			uBackRead = uMaxBack;
		else 
			uBackRead+=BUFREADCOMMENT;
		uReadPos = uSizeFile-uBackRead ;
		uReadSize = ((BUFREADCOMMENT+4) < (uSizeFile-uReadPos)) ? (BUFREADCOMMENT+4) : (uSizeFile-uReadPos);
		if (lufseek(fin,uReadPos,SEEK_SET)!=0) 
			break;
		if (lufread(buf,(uInt)uReadSize,1,fin)!=1) 
			break;
		for (i=(int)uReadSize-3; (i--)>0;)
		{ 
			if (((*(buf+i))==0x50) && ((*(buf+i+1))==0x4b) &&	((*(buf+i+2))==0x05) && ((*(buf+i+3))==0x06))
			{ 
				uPosFound = uReadPos+i;	
				break;
			}
		}
		if (uPosFound!=0) 
			break;
	}
	if (buf) zfree(buf);
	return uPosFound;
}

int unzGoToFirstFile (unzFile file);
int unzCloseCurrentFile (unzFile file);

// Open a Zip file.
// If the zipfile cannot be opened (file don't exist or in not valid), return nullptr.
// Otherwise, the return value is a unzFile Handle, usable with other unzip functions
unzFile unzOpenInternal(LUFILE *fin)
{ 
	if(0) OutputDebugString("unzOpenInternal..\r\n");
	if (fin==nullptr) return nullptr;
	///if (unz_copyright[0]!=' ') {lufclose(fin); return nullptr;}

	int err=UNZ_OK;
	unz_s us;
	uLong central_pos,uL;
	central_pos = unzlocal_SearchCentralDir(fin);
	if (central_pos==0) err=UNZ_ERRNO;
	if (lufseek(fin,central_pos,SEEK_SET)!=0) err=UNZ_ERRNO;
	// the signature, already checked
	if (unzlocal_getLong(fin,&uL)!=UNZ_OK) err=UNZ_ERRNO;
	// number of this disk
	uLong number_disk;          // number of the current dist, used for spanning ZIP, unsupported, always 0
	if (unzlocal_getShort(fin,&number_disk)!=UNZ_OK) err=UNZ_ERRNO;
	// number of the disk with the start of the central directory
	uLong number_disk_with_CD;  // number the the disk with central dir, used for spaning ZIP, unsupported, always 0
	if (unzlocal_getShort(fin,&number_disk_with_CD)!=UNZ_OK) err=UNZ_ERRNO;
	// total number of entries in the central dir on this disk
	if (unzlocal_getShort(fin,&us.gi.number_entry)!=UNZ_OK) err=UNZ_ERRNO;
	// total number of entries in the central dir
	uLong number_entry_CD;      // total number of entries in the central dir (same than number_entry on nospan)
	if (unzlocal_getShort(fin,&number_entry_CD)!=UNZ_OK) err=UNZ_ERRNO;
	if ((number_entry_CD!=us.gi.number_entry) || (number_disk_with_CD!=0) || (number_disk!=0)) err=UNZ_BADZIPFILE;
	// size of the central directory
	if (unzlocal_getLong(fin,&us.size_central_dir)!=UNZ_OK) err=UNZ_ERRNO;
	// offset of start of central directory with respect to the starting disk number
	if (unzlocal_getLong(fin,&us.offset_central_dir)!=UNZ_OK) err=UNZ_ERRNO;
	// zipfile comment length
	if (unzlocal_getShort(fin,&us.gi.size_comment)!=UNZ_OK) err=UNZ_ERRNO;
	if ((central_pos+fin->initial_offset<us.offset_central_dir+us.size_central_dir) && (err==UNZ_OK)) err=UNZ_BADZIPFILE;
	if (err!=UNZ_OK) {lufclose(fin);return nullptr;}

	us.file=fin;
	us.byte_before_the_zipfile = central_pos+fin->initial_offset - (us.offset_central_dir+us.size_central_dir);
	us.central_pos = central_pos;
	us.pfile_in_zip_read = nullptr;
	fin->initial_offset = 0; // since the zipfile itself is expected to handle this

	unz_s *s = (unz_s*)zmalloc(sizeof(unz_s));
	if( s != nullptr ) 
	{
	  *s=us;
	  unzGoToFirstFile((unzFile)s);
	}
	return (unzFile)s;
}

int unzClose (unzFile file)
{
	if(0) OutputDebugString("unzClose..\r\n");
	unz_s* s;
	if (file==nullptr)
		return UNZ_PARAMERROR;
	s=(unz_s*)file;

	if (s->pfile_in_zip_read!=nullptr)
		unzCloseCurrentFile(file);

	lufclose(s->file);
	if (s) zfree(s); // unused s=0;
	return UNZ_OK;
}

int unzGetGlobalInfo (unzFile file,unz_global_info *pglobal_info)
{
	if(0) OutputDebugString("unzGetGlobalInfo..\r\n");
	unz_s* s;
	if (file==nullptr)
		return UNZ_PARAMERROR;
	s=(unz_s*)file;
	*pglobal_info=s->gi;
	return UNZ_OK;
}

//   Translate date/time from Dos format to tm_unz (readable more easilty)
void unzlocal_DosDateToTmuDate (uLong ulDosDate, tm* ptm)
{
	if(0) OutputDebugString("unzlocal_DosDateToTmuDate..\r\n");
	uLong uDate;
	uDate = (uLong)(ulDosDate>>16);
	ptm->tm_mday = (uInt)(uDate&0x1f) ;
	ptm->tm_mon =  (uInt)((((uDate)&0x1E0)/0x20)-1) ;
	ptm->tm_year = (uInt)(((uDate&0x0FE00)/0x0200)+1980) ;

	ptm->tm_hour = (uInt) ((ulDosDate &0xF800)/0x800);
	ptm->tm_min =  (uInt) ((ulDosDate&0x7E0)/0x20) ;
	ptm->tm_sec =  (uInt) (2*(ulDosDate&0x1f)) ;
}

//  Get Info about the current file in the zipfile, with internal only info
int unzlocal_GetCurrentFileInfoInternal (unzFile file, unz_file_info *pfile_info,
										 unz_file_info_internal *pfile_info_internal, char *szFileName,
										 uLong fileNameBufferSize, void *extraField, uLong extraFieldBufferSize,
										 char *szComment, uLong commentBufferSize)
{
	if(0) OutputDebugString("unzlocal_GetCurrentFileInfoInternal..\r\n");
	unz_s* s;
	unz_file_info file_info;
	unz_file_info_internal file_info_internal;
	int err=UNZ_OK;
	uLong uMagic;
	long lSeek=0;

	if (file==nullptr)
		return UNZ_PARAMERROR;
	s=(unz_s*)file;
	if (lufseek(s->file,s->pos_in_central_dir+s->byte_before_the_zipfile,SEEK_SET)!=0)
		err=UNZ_ERRNO;


	// we check the magic
	if (err==UNZ_OK)
		if (unzlocal_getLong(s->file,&uMagic) != UNZ_OK)
			err=UNZ_ERRNO;
		else if (uMagic!=0x02014b50)
			err=UNZ_BADZIPFILE;

	if (unzlocal_getShort(s->file,&file_info.version) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getShort(s->file,&file_info.version_needed) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getShort(s->file,&file_info.flag) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getShort(s->file,&file_info.compression_method) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getLong(s->file,&file_info.dosDate) != UNZ_OK)
		err=UNZ_ERRNO;

	unzlocal_DosDateToTmuDate(file_info.dosDate,&file_info.tmu_date);

	if (unzlocal_getLong(s->file,&file_info.crc) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getLong(s->file,&file_info.compressed_size) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getLong(s->file,&file_info.uncompressed_size) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getShort(s->file,&file_info.size_filename) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getShort(s->file,&file_info.size_file_extra) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getShort(s->file,&file_info.size_file_comment) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getShort(s->file,&file_info.disk_num_start) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getShort(s->file,&file_info.internal_fa) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getLong(s->file,&file_info.external_fa) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getLong(s->file,&file_info_internal.offset_curfile) != UNZ_OK)
		err=UNZ_ERRNO;

	lSeek+=file_info.size_filename;
	if ((err==UNZ_OK) && (szFileName!=nullptr))
	{
		uLong uSizeRead ;
		if (file_info.size_filename<fileNameBufferSize)
		{
			*(szFileName+file_info.size_filename)='\0';
			uSizeRead = file_info.size_filename;
		}
		else
			uSizeRead = fileNameBufferSize;

		if ((file_info.size_filename>0) && (fileNameBufferSize>0))
			if (lufread(szFileName,(uInt)uSizeRead,1,s->file)!=1)
				err=UNZ_ERRNO;
		lSeek -= uSizeRead;
	}


	if ((err==UNZ_OK) && (extraField!=nullptr))
	{
		uLong uSizeRead ;
		if (file_info.size_file_extra<extraFieldBufferSize)
			uSizeRead = file_info.size_file_extra;
		else
			uSizeRead = extraFieldBufferSize;

		if (lSeek!=0)
			if (lufseek(s->file,lSeek,SEEK_CUR)==0)
				lSeek=0;
			else
				err=UNZ_ERRNO;
		if ((file_info.size_file_extra>0) && (extraFieldBufferSize>0))
			if (lufread(extraField,(uInt)uSizeRead,1,s->file)!=1)
				err=UNZ_ERRNO;
		lSeek += file_info.size_file_extra - uSizeRead;
	}
	else
		lSeek+=file_info.size_file_extra;


	if ((err==UNZ_OK) && (szComment!=nullptr))
	{
		uLong uSizeRead ;
		if (file_info.size_file_comment<commentBufferSize)
		{
			*(szComment+file_info.size_file_comment)='\0';
			uSizeRead = file_info.size_file_comment;
		}
		else
			uSizeRead = commentBufferSize;

		if (lSeek!=0)
			if (lufseek(s->file,lSeek,SEEK_CUR)==0)
			{} // unused lSeek=0;
			else
				err=UNZ_ERRNO;
		if ((file_info.size_file_comment>0) && (commentBufferSize>0))
			if (lufread(szComment,(uInt)uSizeRead,1,s->file)!=1)
				err=UNZ_ERRNO;
		//unused lSeek+=file_info.size_file_comment - uSizeRead;
	}
	else {} //unused lSeek+=file_info.size_file_comment;

	if ((err==UNZ_OK) && (pfile_info!=nullptr))
		*pfile_info=file_info;

	if ((err==UNZ_OK) && (pfile_info_internal!=nullptr))
		*pfile_info_internal=file_info_internal;

	return err;
}



//  Write info about the ZipFile in the *pglobal_info structure.
//  No preparation of the structure is needed
//  return UNZ_OK if there is no problem.
int unzGetCurrentFileInfo (unzFile file, unz_file_info *pfile_info,
						   char *szFileName, uLong fileNameBufferSize, 
						   void *extraField, uLong extraFieldBufferSize,
						   char *szComment, uLong commentBufferSize)
{ 
	if(0) OutputDebugString("unzGetCurrentFileInfo..\r\n");
	return unzlocal_GetCurrentFileInfoInternal(file,pfile_info,nullptr,szFileName,fileNameBufferSize,
		extraField,extraFieldBufferSize, szComment,commentBufferSize);
}


//  Set the current file of the zipfile to the first file.
//  return UNZ_OK if there is no problem
int unzGoToFirstFile (unzFile file)
{
	if(0) OutputDebugString("unzGoToFirstFile..\r\n");
	int err;
	unz_s* s;
	if (file==nullptr) return UNZ_PARAMERROR;
	s=(unz_s*)file;
	s->pos_in_central_dir=s->offset_central_dir;
	s->num_file=0;
	err=unzlocal_GetCurrentFileInfoInternal(file,&s->cur_file_info,	&s->cur_file_info_internal,	nullptr,0,nullptr,0,nullptr,0);
	s->current_file_ok = (err == UNZ_OK);
	return err;
}


//  Set the current file of the zipfile to the next file.
//  return UNZ_OK if there is no problem
//  return UNZ_END_OF_LIST_OF_FILE if the actual file was the latest.
int unzGoToNextFile (unzFile file)
{
	if(0) OutputDebugString("unzGoToNextFile..\r\n");
	unz_s* s;
	int err;

	if (file==nullptr)
		return UNZ_PARAMERROR;
	s=(unz_s*)file;
	if (!s->current_file_ok)
		return UNZ_END_OF_LIST_OF_FILE;
	if (s->num_file+1==s->gi.number_entry)
		return UNZ_END_OF_LIST_OF_FILE;

	s->pos_in_central_dir += SIZECENTRALDIRITEM + s->cur_file_info.size_filename +
		s->cur_file_info.size_file_extra + s->cur_file_info.size_file_comment ;
	s->num_file++;
	err = unzlocal_GetCurrentFileInfoInternal(file,&s->cur_file_info,
		&s->cur_file_info_internal,
		nullptr,0,nullptr,0,nullptr,0);
	s->current_file_ok = (err == UNZ_OK);
	return err;
}


//  Try locate the file szFileName in the zipfile.
//  For the iCaseSensitivity signification, see unzStringFileNameCompare
//  return value :
//  UNZ_OK if the file is found. It becomes the current file.
//  UNZ_END_OF_LIST_OF_FILE if the file is not found
int unzLocateFile (unzFile file, const TCHAR *szFileName, int iCaseSensitivity)
{
	if(0) OutputDebugString("unzLocateFile..\r\n");
	unz_s* s;
	int err;

	uLong num_fileSaved;
	uLong pos_in_central_dirSaved;

	if (file==nullptr)
		return UNZ_PARAMERROR;

	if (lstrlen(szFileName)>=UNZ_MAXFILENAMEINZIP)
		return UNZ_PARAMERROR;

	char szFileNameA[MAX_PATH];

	s=(unz_s*)file;
	if (!s->current_file_ok)
		return UNZ_END_OF_LIST_OF_FILE;

	num_fileSaved = s->num_file;
	pos_in_central_dirSaved = s->pos_in_central_dir;

	err = unzGoToFirstFile(file);

	while (err == UNZ_OK)
	{
		char szCurrentFileName[UNZ_MAXFILENAMEINZIP+1];
		unzGetCurrentFileInfo(file,nullptr,
			szCurrentFileName,sizeof(szCurrentFileName)-1,
			nullptr,0,nullptr,0);
		if (unzStringFileNameCompare(szCurrentFileName,szFileNameA,iCaseSensitivity)==0)
			return UNZ_OK;
		err = unzGoToNextFile(file);
	}

	s->num_file = num_fileSaved ;
	s->pos_in_central_dir = pos_in_central_dirSaved ;
	return err;
}

//  Read the local header of the current zipfile
//  Check the coherency of the local header and info in the end of central
//        directory about this file
//  store in *piSizeVar the size of extra info in local header
//        (filename and size of extra field data)
int unzlocal_CheckCurrentFileCoherencyHeader (unz_s *s,uInt *piSizeVar,
											  uLong *poffset_local_extrafield, uInt  *psize_local_extrafield)
{
	if(0) OutputDebugString("unzlocal_CheckCurrentFileCoherencyHeader..\r\n");
	uLong uMagic,uData,uFlags;
	uLong size_filename;
	uLong size_extra_field;
	int err=UNZ_OK;

	*piSizeVar = 0;
	*poffset_local_extrafield = 0;
	*psize_local_extrafield = 0;

	if (lufseek(s->file,s->cur_file_info_internal.offset_curfile + s->byte_before_the_zipfile,SEEK_SET)!=0)
		return UNZ_ERRNO;


	if (err==UNZ_OK)
		if (unzlocal_getLong(s->file,&uMagic) != UNZ_OK)
			err=UNZ_ERRNO;	
		else
		{
			if (uMagic!=0x04034b50)
			{
				if(uMagic!=0x00010001)	
					err=UNZ_BADZIPFILE;
			}
		}

	if (unzlocal_getShort(s->file,&uData) != UNZ_OK)
		err=UNZ_ERRNO;
	//	else if ((err==UNZ_OK) && (uData!=s->cur_file_info.wVersion))
	//		err=UNZ_BADZIPFILE;
	if (unzlocal_getShort(s->file,&uFlags) != UNZ_OK)
		err=UNZ_ERRNO;

	if (unzlocal_getShort(s->file,&uData) != UNZ_OK)
		err=UNZ_ERRNO;
	else if ((err==UNZ_OK) && (uData!=s->cur_file_info.compression_method))
		err=UNZ_BADZIPFILE;

	if ((err==UNZ_OK) && (s->cur_file_info.compression_method!=0) &&
		(s->cur_file_info.compression_method!=Z_DEFLATED))
		err=UNZ_BADZIPFILE;

	if (unzlocal_getLong(s->file,&uData) != UNZ_OK) // date/time
		err=UNZ_ERRNO;

	if (unzlocal_getLong(s->file,&uData) != UNZ_OK) // crc
		err=UNZ_ERRNO;
	else if ((err==UNZ_OK) && (uData!=s->cur_file_info.crc) &&
		((uFlags & 8)==0))
		err=UNZ_BADZIPFILE;

	if (unzlocal_getLong(s->file,&uData) != UNZ_OK) // size compr
		err=UNZ_ERRNO;
	else if ((err==UNZ_OK) && (uData!=s->cur_file_info.compressed_size) &&
		((uFlags & 8)==0))
		err=UNZ_BADZIPFILE;

	if (unzlocal_getLong(s->file,&uData) != UNZ_OK) // size uncompr
		err=UNZ_ERRNO;
	else if ((err==UNZ_OK) && (uData!=s->cur_file_info.uncompressed_size) &&
		((uFlags & 8)==0))
		err=UNZ_BADZIPFILE;


	if (unzlocal_getShort(s->file,&size_filename) != UNZ_OK)
		err=UNZ_ERRNO;
	else if ((err==UNZ_OK) && (size_filename!=s->cur_file_info.size_filename))
		err=UNZ_BADZIPFILE;

	*piSizeVar += (uInt)size_filename;

	if (unzlocal_getShort(s->file,&size_extra_field) != UNZ_OK)
		err=UNZ_ERRNO;
	*poffset_local_extrafield= s->cur_file_info_internal.offset_curfile +
		SIZEZIPLOCALHEADER + size_filename;
	*psize_local_extrafield = (uInt)size_extra_field;

	*piSizeVar += (uInt)size_extra_field;

	return err;
}

//  Open for reading data the current file in the zipfile.
//  If there is no error and the file is opened, the return value is UNZ_OK.
int unzOpenCurrentFile (unzFile file)
{
	if(0) OutputDebugString("unzOpenCurrentFile..\r\n");
	int err;
	int Store;
	uInt iSizeVar;
	unz_s* s;
	file_in_zip_read_info_s* pfile_in_zip_read_info;
	uLong offset_local_extrafield;  // offset of the local extra field
	uInt  size_local_extrafield;    // size of the local extra field

	if (file==nullptr)
		return UNZ_PARAMERROR;
	s=(unz_s*)file;
	if (!s->current_file_ok)
		return UNZ_PARAMERROR;

	if (s->pfile_in_zip_read != nullptr)
		unzCloseCurrentFile(file);

	if (unzlocal_CheckCurrentFileCoherencyHeader(s,&iSizeVar,
		&offset_local_extrafield,&size_local_extrafield)!=UNZ_OK)
		return UNZ_BADZIPFILE;

	pfile_in_zip_read_info = (file_in_zip_read_info_s*)zmalloc(sizeof(file_in_zip_read_info_s));
	if (pfile_in_zip_read_info==nullptr)
		return UNZ_INTERNALERROR;

	pfile_in_zip_read_info->read_buffer=(char*)zmalloc(UNZ_BUFSIZE);
	pfile_in_zip_read_info->offset_local_extrafield = offset_local_extrafield;
	pfile_in_zip_read_info->size_local_extrafield = size_local_extrafield;
	pfile_in_zip_read_info->pos_local_extrafield=0;

	if (pfile_in_zip_read_info->read_buffer==nullptr)
	{
		if (pfile_in_zip_read_info!=0) zfree(pfile_in_zip_read_info); //unused pfile_in_zip_read_info=0;
		return UNZ_INTERNALERROR;
	}

	pfile_in_zip_read_info->stream_initialised=0;

	if ((s->cur_file_info.compression_method!=0) && (s->cur_file_info.compression_method!=Z_DEFLATED))
	{ // unused err=UNZ_BADZIPFILE;
	}
	Store = s->cur_file_info.compression_method==0;

	pfile_in_zip_read_info->crc32_wait=s->cur_file_info.crc;
	pfile_in_zip_read_info->crc32=0;
	pfile_in_zip_read_info->compression_method =
		s->cur_file_info.compression_method;
	pfile_in_zip_read_info->file=s->file;
	pfile_in_zip_read_info->byte_before_the_zipfile=s->byte_before_the_zipfile;

	pfile_in_zip_read_info->stream.total_out = 0;

	if (!Store)
	{
		pfile_in_zip_read_info->stream.zalloc = (alloc_func)0;
		pfile_in_zip_read_info->stream.zfree = (free_func)0;
		pfile_in_zip_read_info->stream.opaque = (voidpf)0;

		err=inflateInit2(&pfile_in_zip_read_info->stream);
		if (err == Z_OK)
			pfile_in_zip_read_info->stream_initialised=1;
		// windowBits is passed < 0 to tell that there is no zlib header.
		// Note that in this case inflate *requires* an extra "dummy" byte
		// after the compressed stream in order to complete decompression and
		// return Z_STREAM_END.
		// In unzip, i don't wait absolutely Z_STREAM_END because I known the
		// size of both compressed and uncompressed data
	}
	pfile_in_zip_read_info->rest_read_compressed =
		s->cur_file_info.compressed_size ;
	pfile_in_zip_read_info->rest_read_uncompressed =
		s->cur_file_info.uncompressed_size ;


	pfile_in_zip_read_info->pos_in_zipfile =
		s->cur_file_info_internal.offset_curfile + SIZEZIPLOCALHEADER +
		iSizeVar;

	pfile_in_zip_read_info->stream.avail_in = (uInt)0;


	s->pfile_in_zip_read = pfile_in_zip_read_info;
	return UNZ_OK;
}

//  Read bytes from the current file.
//  buf contain buffer where data must be copied
//  len the size of buf.
//  return the number of byte copied if somes bytes are copied
//  return 0 if the end of file was reached
//  return <0 with error code if there is an error
//    (UNZ_ERRNO for IO error, or zLib error for uncompress error)
int unzReadCurrentFile(unzFile file, voidp buf, unsigned len)
{ 
	if(0) OutputDebugString("unzReadCurrentFile..\r\n");
	int err=UNZ_OK;
	uInt iRead = 0;

	unz_s *s = (unz_s*)file;
	if (s==nullptr) 
		return UNZ_PARAMERROR;

	file_in_zip_read_info_s* pfile_in_zip_read_info = s->pfile_in_zip_read;
	if (pfile_in_zip_read_info==nullptr) 
		return UNZ_PARAMERROR;
	if ((pfile_in_zip_read_info->read_buffer == nullptr)) 
		return UNZ_END_OF_LIST_OF_FILE;
	if (len==0) 
		return 0;

	pfile_in_zip_read_info->stream.next_out = (Byte*)buf;
	pfile_in_zip_read_info->stream.avail_out = (uInt)len;

	if (len>pfile_in_zip_read_info->rest_read_uncompressed)
	{ 
		pfile_in_zip_read_info->stream.avail_out = (uInt)pfile_in_zip_read_info->rest_read_uncompressed;
	}

	while (pfile_in_zip_read_info->stream.avail_out>0)
	{ 
		if ((pfile_in_zip_read_info->stream.avail_in==0) && (pfile_in_zip_read_info->rest_read_compressed>0))
		{ 
			uInt uReadThis = UNZ_BUFSIZE;
			if (pfile_in_zip_read_info->rest_read_compressed<uReadThis) uReadThis = (uInt)pfile_in_zip_read_info->rest_read_compressed;
			if (uReadThis == 0) 
				return UNZ_EOF;
			if (lufseek(pfile_in_zip_read_info->file, pfile_in_zip_read_info->pos_in_zipfile + pfile_in_zip_read_info->byte_before_the_zipfile,SEEK_SET)!=0) 
				return UNZ_ERRNO;
			if (lufread(pfile_in_zip_read_info->read_buffer,uReadThis,1,pfile_in_zip_read_info->file)!=1) 
				return UNZ_ERRNO;
			pfile_in_zip_read_info->pos_in_zipfile += uReadThis;
			pfile_in_zip_read_info->rest_read_compressed-=uReadThis;
			pfile_in_zip_read_info->stream.next_in = (Byte*)pfile_in_zip_read_info->read_buffer;
			pfile_in_zip_read_info->stream.avail_in = (uInt)uReadThis;
		}

		if (pfile_in_zip_read_info->compression_method==0)
		{
			uInt uDoCopy,i ;
			if (pfile_in_zip_read_info->stream.avail_out < pfile_in_zip_read_info->stream.avail_in)
			{ 
				uDoCopy = pfile_in_zip_read_info->stream.avail_out ;
			}
			else
			{ uDoCopy = pfile_in_zip_read_info->stream.avail_in ;
			}
			for (i=0;i<uDoCopy;i++)
			{ 
				*(pfile_in_zip_read_info->stream.next_out+i) = *(pfile_in_zip_read_info->stream.next_in+i);
			}
			pfile_in_zip_read_info->crc32 = ucrc32(pfile_in_zip_read_info->crc32,pfile_in_zip_read_info->stream.next_out,uDoCopy);
			pfile_in_zip_read_info->rest_read_uncompressed-=uDoCopy;
			pfile_in_zip_read_info->stream.avail_in -= uDoCopy;
			pfile_in_zip_read_info->stream.avail_out -= uDoCopy;
			pfile_in_zip_read_info->stream.next_out += uDoCopy;
			pfile_in_zip_read_info->stream.next_in += uDoCopy;
			pfile_in_zip_read_info->stream.total_out += uDoCopy;
			iRead += uDoCopy;
		}
		else
		{ 
			uLong uTotalOutBefore,uTotalOutAfter;
			const Byte *bufBefore;
			uLong uOutThis;
			int flush=Z_SYNC_FLUSH;
			uTotalOutBefore = pfile_in_zip_read_info->stream.total_out;
			bufBefore = pfile_in_zip_read_info->stream.next_out;
			err=inflate(&pfile_in_zip_read_info->stream,flush);
			uTotalOutAfter = pfile_in_zip_read_info->stream.total_out;
			uOutThis = uTotalOutAfter-uTotalOutBefore;
			pfile_in_zip_read_info->crc32 = ucrc32(pfile_in_zip_read_info->crc32,bufBefore,(uInt)(uOutThis));
			pfile_in_zip_read_info->rest_read_uncompressed -= uOutThis;
			iRead += (uInt)(uTotalOutAfter - uTotalOutBefore);
			if (err==Z_STREAM_END) return (iRead==len) ? UNZ_EOF : iRead;
			if (err!=Z_OK) break;
		}
	}

	if (err==Z_OK) return iRead;
	return err;
}


//  Give the current position in uncompressed data
z_off_t unztell (unzFile file)
{
	if(0) OutputDebugString("unztell..\r\n");
	unz_s* s;
	file_in_zip_read_info_s* pfile_in_zip_read_info;
	if (file==nullptr)
		return UNZ_PARAMERROR;
	s=(unz_s*)file;
	pfile_in_zip_read_info=s->pfile_in_zip_read;

	if (pfile_in_zip_read_info==nullptr)
		return UNZ_PARAMERROR;

	return (z_off_t)pfile_in_zip_read_info->stream.total_out;
}


//  return 1 if the end of file was reached, 0 elsewhere
int unzeof (unzFile file)
{
	if(0) OutputDebugString("unzeof..\r\n");
	unz_s* s;
	file_in_zip_read_info_s* pfile_in_zip_read_info;
	if (file==nullptr)
		return UNZ_PARAMERROR;
	s=(unz_s*)file;
	pfile_in_zip_read_info=s->pfile_in_zip_read;

	if (pfile_in_zip_read_info==nullptr)
		return UNZ_PARAMERROR;

	if (pfile_in_zip_read_info->rest_read_uncompressed == 0)
		return 1;
	else
		return 0;
}

//  Read extra field from the current file (opened by unzOpenCurrentFile)
//  This is the local-header version of the extra field (sometimes, there is
//    more info in the local-header version than in the central-header)
//  if buf==nullptr, it return the size of the local extra field that can be read
//  if buf!=nullptr, len is the size of the buffer, the extra header is copied in buf.
//  the return value is the number of bytes copied in buf, or (if <0) the error code
int unzGetLocalExtrafield (unzFile file,voidp buf,unsigned len)
{
	if(0) OutputDebugString("unzGetLocalExtrafield..\r\n");
	unz_s* s;
	file_in_zip_read_info_s* pfile_in_zip_read_info;
	uInt read_now;
	uLong size_to_read;

	if (file==nullptr)
		return UNZ_PARAMERROR;
	s=(unz_s*)file;
	pfile_in_zip_read_info=s->pfile_in_zip_read;

	if (pfile_in_zip_read_info==nullptr)
		return UNZ_PARAMERROR;

	size_to_read = (pfile_in_zip_read_info->size_local_extrafield -
		pfile_in_zip_read_info->pos_local_extrafield);

	if (buf==nullptr)
		return (int)size_to_read;

	if (len>size_to_read)
		read_now = (uInt)size_to_read;
	else
		read_now = (uInt)len ;

	if (read_now==0)
		return 0;

	if (lufseek(pfile_in_zip_read_info->file, pfile_in_zip_read_info->offset_local_extrafield +  pfile_in_zip_read_info->pos_local_extrafield,SEEK_SET)!=0)
		return UNZ_ERRNO;

	if (lufread(buf,(uInt)size_to_read,1,pfile_in_zip_read_info->file)!=1)
		return UNZ_ERRNO;

	return (int)read_now;
}

//  Close the file in zip opened with unzipOpenCurrentFile
//  Return UNZ_CRCERROR if all the file was read but the CRC is not good
int unzCloseCurrentFile (unzFile file)
{
	if(0) OutputDebugString("unzCloseCurrentFile..\r\n");
	int err=UNZ_OK;

	unz_s* s;
	file_in_zip_read_info_s* pfile_in_zip_read_info;
	if (file==nullptr)
		return UNZ_PARAMERROR;
	s=(unz_s*)file;
	pfile_in_zip_read_info=s->pfile_in_zip_read;

	if (pfile_in_zip_read_info==nullptr)
		return UNZ_PARAMERROR;

	if (pfile_in_zip_read_info->rest_read_uncompressed == 0)
	{
		if (pfile_in_zip_read_info->crc32 != pfile_in_zip_read_info->crc32_wait)
			err=UNZ_CRCERROR;
	}

	if (pfile_in_zip_read_info->read_buffer!=0)
	{ 
		void *buf = pfile_in_zip_read_info->read_buffer;
		zfree(buf);
		pfile_in_zip_read_info->read_buffer=0;
	}
	pfile_in_zip_read_info->read_buffer = nullptr;
	if (pfile_in_zip_read_info->stream_initialised)
		inflateEnd(&pfile_in_zip_read_info->stream);

	pfile_in_zip_read_info->stream_initialised = 0;
	if (pfile_in_zip_read_info!=0) 
		zfree(pfile_in_zip_read_info); // unused pfile_in_zip_read_info=0;

	s->pfile_in_zip_read=nullptr;

	return err;
}


//  Get the global comment string of the ZipFile, in the szComment buffer.
//  uSizeBuf is the size of the szComment buffer.
//  return the number of byte copied or an error code <0
int unzGetGlobalComment (unzFile file, char *szComment, uLong uSizeBuf)
{ 
	if(0) OutputDebugString("unzGetGlobalComment..\r\n");
	//int err=UNZ_OK;
	unz_s* s;
	uLong uReadThis ;
	if (file==nullptr) 
		return UNZ_PARAMERROR;
	s=(unz_s*)file;
	uReadThis = uSizeBuf;
	if (uReadThis>s->gi.size_comment) 
		uReadThis = s->gi.size_comment;
	if (lufseek(s->file,s->central_pos+22,SEEK_SET)!=0) 
		return UNZ_ERRNO;
	if (uReadThis>0)
	{ 
		*szComment='\0';
		if (lufread(szComment,(uInt)uReadThis,1,s->file)!=1) 
			return UNZ_ERRNO;
	}
	if ((szComment != nullptr) && (uSizeBuf > s->gi.size_comment)) 
		*(szComment+s->gi.size_comment)='\0';
	return (int)uReadThis;
}


