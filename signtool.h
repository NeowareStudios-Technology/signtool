/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef SIGNTOOL_H
#define SIGNTOOL_H

#define DJN_TEST

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "include/prprf.h"
#include "include/prio.h"
#include "include/secutil.h"
#include "include/ocsp.h"
#include "include/jar.h"
#include "include/jarfile.h"
#include "include/secpkcs7.h"
#include "include/pk11func.h"
#include "include/secmod.h"
#include "include/plhash.h"
#include "include/nss.h"

#ifdef _UNIX
#include <unistd.h>
#endif

/**********************************************************************
 * General Defines
 */
#define JAR_BASE_END JAR_BASE + 100
#define ERRX (-1)  /* the exit code used on failure */
#define FNSIZE 256 /* the maximum length for filenames */
#define MAX_RSA_KEY_SIZE 4096
#define DEFAULT_RSA_KEY_SIZE 1024
#define MANIFEST "manifest.mf"
#define DEFAULT_X509_BASENAME "x509"
#define DEFAULT_COMMON_NAME "Signtool " NSS_VERSION " Testing Certificate"
#define CREATOR "Signtool (signtool " NSS_VERSION ")"
#define BREAKAGE "PLEASE DO NOT EDIT THIS FILE. YOU WILL BREAK IT."
#define MIN_COMPRESSION_LEVEL (-1)
#define MAX_COMPRESSION_LEVEL 9
#define DEFAULT_COMPRESSION_LEVEL (-1) /* zlib understands this to be default*/
#define STDIN_BUF_SIZE 160
#define PROGRAM_NAME "signtool"
#define LONG_PROGRAM_NAME "Signing Tool"
#define DEFAULT_BASE_NAME "zigbert"
#define TMP_OUTPUT "signtool.tmp"
#define XPI_TEXT "Creating XPI Compatible Archive"

/***************************************************************
 * Main Task Functions
 */
int GenerateCert(char *nickname, int keysize, char *token);
int ListCerts(char *key, int list_certs);
int VerifyJar(char *filename);
int SignArchive(char *tree, char *keyName, char *zip_file, int javascript,
                char *meta_file, char *install_script, int _optimize, PRBool recurse);
int SignAllArc(char *jartree, char *keyName, int javascript, char *metafile,
               char *install_script, int optimize, PRBool recurse);
int InlineJavaScript(char *dir, PRBool recurse);
int JarWho(char *filename);
void JarListModules(void);

/**************************************************************
 * Utility Functions
 */
CERTCertDBHandle *OpenCertDB(PRBool readOnly);

int RemoveAllArc(char *tree);
void VerifyCertDir(char *dir, char *keyName);
int InitCrypto(char *cert_dir, PRBool readOnly);
int foreach (char *dirname, char *prefix,
             int (*fn)(char *filename, char *dirname, char *basedir, char *base, void *arg),
             PRBool recurse, PRBool includeDirs, void *arg);
void print_error(int i);
void give_help(int status);
const char *secErrorString(long code);
void displayVerifyLog(CERTVerifyLog *log);
void Usage(void);
void LongUsage(void);
char *chop(char *);
void out_of_memory(void);
void FatalError(char *msg);
char *get_default_cert_dir(void);
SECItem *password_hardcode(void *arg, void *handle);
char *pk11_password_hardcode(PK11SlotInfo *slot, PRBool retry, void *arg);
int rm_dash_r(char *path);
char *pr_fgets(char *buf, int size, PRFileDesc *file);

/*****************************************************************
 * Global Variables (*gag*)
 */
extern char *password;           /* the password passed in on the command line */
extern PLHashTable *excludeDirs; /* directory entry to skip while recursing */
extern int no_time;
extern int xpi_arc;
extern char *base; /* basename of ".rsa" and ".sf" files */
extern long *mozilla_event_queue;
extern char *progName;          /* argv[0] */
extern PLHashTable *extensions; /* only sign files with this extension */
extern PRBool extensionsGiven;
extern char *scriptdir;
extern int compression_level;
extern PRFileDesc *outputFD, *errorFD;
extern int verbosity;
extern int errorCount;
extern int warningCount;
extern secuPWData pwdata;

#endif /* SIGNTOOL_H */
