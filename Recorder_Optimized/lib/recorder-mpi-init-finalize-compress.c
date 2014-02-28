/*
 *  (C) 2012 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

#define _XOPEN_SOURCE 500
#define _GNU_SOURCE /* for RTLD_NEXT */

#include "recorder-runtime-config.h"

#include <stdlib.h>
#include <stdio.h>

#include "mpi.h"
#include "recorder.h"
#include "recorder-dynamic.h"

#ifdef RECORDER_PRELOAD

#include <dlfcn.h>

#define RECORDER_FORWARD_DECL(name,ret,args) \
  ret (*__real_ ## name)args = NULL;

#include "simple_compress.h"

// make it compatible with c++
extern int recorder_mpi_initialize(int*, char***);
extern SimpleCompress *sc;
#define RECORDER_TYPE(name, ret, args) \
	typedef ret (* TYPE_##name)args;


#define MAP_OR_FAIL(func) \
    __real_ ## func = (TYPE_##func)dlsym(RTLD_NEXT, #func); \
    if (!(__real_ ## func)) { \
        fprintf(stderr, "Darshan failed to map symbol: %s\n", #func); \
    }

RECORDER_FORWARD_DECL(PMPI_File_close, int, (MPI_File *fh));
RECORDER_FORWARD_DECL(PMPI_File_set_size, int, (MPI_File fh, MPI_Offset size));
RECORDER_FORWARD_DECL(PMPI_File_iread_at, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request));
RECORDER_FORWARD_DECL(PMPI_File_iread, int, (MPI_File fh, void  *buf, int  count, MPI_Datatype  datatype, __D_MPI_REQUEST  *request));
RECORDER_FORWARD_DECL(PMPI_File_iread_shared, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request));
RECORDER_FORWARD_DECL(PMPI_File_iwrite_at, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request));
RECORDER_FORWARD_DECL(PMPI_File_iwrite, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request));
RECORDER_FORWARD_DECL(PMPI_File_iwrite_shared, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request));
RECORDER_FORWARD_DECL(PMPI_File_open, int, (MPI_Comm comm, char *filename, int amode, MPI_Info info, MPI_File *fh));
RECORDER_FORWARD_DECL(PMPI_File_read_all_begin, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype));
RECORDER_FORWARD_DECL(PMPI_File_read_all, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_FORWARD_DECL(PMPI_File_read_at_all, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_FORWARD_DECL(PMPI_File_read_at_all_begin, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype));
RECORDER_FORWARD_DECL(PMPI_File_read_at, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_FORWARD_DECL(PMPI_File_read, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_FORWARD_DECL(PMPI_File_read_ordered_begin, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype));
RECORDER_FORWARD_DECL(PMPI_File_read_ordered, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_FORWARD_DECL(PMPI_File_read_shared, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_FORWARD_DECL(PMPI_File_set_view, int, (MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, char *datarep, MPI_Info info));
RECORDER_FORWARD_DECL(PMPI_File_sync, int, (MPI_File fh));
RECORDER_FORWARD_DECL(PMPI_File_write_all_begin, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype));
RECORDER_FORWARD_DECL(PMPI_File_write_all, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_FORWARD_DECL(PMPI_File_write_at_all_begin, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype));
RECORDER_FORWARD_DECL(PMPI_File_write_at_all, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_FORWARD_DECL(PMPI_File_write_at, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_FORWARD_DECL(PMPI_File_write, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_FORWARD_DECL(PMPI_File_write_ordered_begin, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype));
RECORDER_FORWARD_DECL(PMPI_File_write_ordered, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_FORWARD_DECL(PMPI_File_write_shared, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_FORWARD_DECL(PMPI_Comm_rank, int, (MPI_Comm comm, int *rank));
RECORDER_FORWARD_DECL(PMPI_Comm_size, int, (MPI_Comm comm, int *size));
RECORDER_FORWARD_DECL(PMPI_Finalize, int, ());
RECORDER_FORWARD_DECL(PMPI_Init, int, (int *argc, char ***argv));
RECORDER_FORWARD_DECL(PMPI_Init_thread, int, (int *argc, char ***argv, int required, int *provided));

RECORDER_FORWARD_DECL(PMPI_Wtime, double, ());
RECORDER_FORWARD_DECL(PMPI_Allreduce, int, (void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm));
RECORDER_FORWARD_DECL(PMPI_Bcast, int, (void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm));
RECORDER_FORWARD_DECL(PMPI_Scan, int, (void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm));
RECORDER_FORWARD_DECL(PMPI_Type_commit, int, (MPI_Datatype *datatype));
RECORDER_FORWARD_DECL(PMPI_Type_contiguous, int, (int count, MPI_Datatype oldtype, MPI_Datatype *newtype));
RECORDER_FORWARD_DECL(PMPI_Type_extent, int, (MPI_Datatype datatype, MPI_Aint *extent));
RECORDER_FORWARD_DECL(PMPI_Type_free, int, (MPI_Datatype *datatype));
RECORDER_FORWARD_DECL(PMPI_Type_hindexed, int, (int count, int *array_of_blocklengths, MPI_Aint *array_of_displacements, MPI_Datatype oldtype, MPI_Datatype *newtype));
RECORDER_FORWARD_DECL(PMPI_Op_create, int, (MPI_User_function *function, int commute, MPI_Op *op));
RECORDER_FORWARD_DECL(PMPI_Op_free, int, (MPI_Op *op));
RECORDER_FORWARD_DECL(PMPI_Reduce, int, (void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm));
RECORDER_FORWARD_DECL(PMPI_Type_get_envelope, int, (MPI_Datatype datatype, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner));
RECORDER_FORWARD_DECL(PMPI_Type_size, int, (MPI_Datatype datatype, int *size));

// get it by s/FORWARD_DECL/TYPE/
RECORDER_TYPE(PMPI_File_close, int, (MPI_File *fh));
RECORDER_TYPE(PMPI_File_set_size, int, (MPI_File fh, MPI_Offset size));
RECORDER_TYPE(PMPI_File_iread_at, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request));
RECORDER_TYPE(PMPI_File_iread, int, (MPI_File fh, void  *buf, int  count, MPI_Datatype  datatype, __D_MPI_REQUEST  *request));
RECORDER_TYPE(PMPI_File_iread_shared, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request));
RECORDER_TYPE(PMPI_File_iwrite_at, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request));
RECORDER_TYPE(PMPI_File_iwrite, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request));
RECORDER_TYPE(PMPI_File_iwrite_shared, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request));
RECORDER_TYPE(PMPI_File_open, int, (MPI_Comm comm, char *filename, int amode, MPI_Info info, MPI_File *fh));
RECORDER_TYPE(PMPI_File_read_all_begin, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype));
RECORDER_TYPE(PMPI_File_read_all, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_TYPE(PMPI_File_read_at_all, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_TYPE(PMPI_File_read_at_all_begin, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype));
RECORDER_TYPE(PMPI_File_read_at, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_TYPE(PMPI_File_read, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_TYPE(PMPI_File_read_ordered_begin, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype));
RECORDER_TYPE(PMPI_File_read_ordered, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_TYPE(PMPI_File_read_shared, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_TYPE(PMPI_File_set_view, int, (MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, char *datarep, MPI_Info info));
RECORDER_TYPE(PMPI_File_sync, int, (MPI_File fh));
RECORDER_TYPE(PMPI_File_write_all_begin, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype));
RECORDER_TYPE(PMPI_File_write_all, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_TYPE(PMPI_File_write_at_all_begin, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype));
RECORDER_TYPE(PMPI_File_write_at_all, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_TYPE(PMPI_File_write_at, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_TYPE(PMPI_File_write, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_TYPE(PMPI_File_write_ordered_begin, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype));
RECORDER_TYPE(PMPI_File_write_ordered, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_TYPE(PMPI_File_write_shared, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_TYPE(PMPI_Comm_rank, int, (MPI_Comm comm, int *rank));
RECORDER_TYPE(PMPI_Comm_size, int, (MPI_Comm comm, int *size));
RECORDER_TYPE(PMPI_Finalize, int, ());
RECORDER_TYPE(PMPI_Init, int, (int *argc, char ***argv));
RECORDER_TYPE(PMPI_Init_thread, int, (int *argc, char ***argv, int required, int *provided));

RECORDER_TYPE(PMPI_Wtime, double, ());
RECORDER_TYPE(PMPI_Allreduce, int, (void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm));
RECORDER_TYPE(PMPI_Bcast, int, (void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm));
RECORDER_TYPE(PMPI_Scan, int, (void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm));
RECORDER_TYPE(PMPI_Type_commit, int, (MPI_Datatype *datatype));
RECORDER_TYPE(PMPI_Type_contiguous, int, (int count, MPI_Datatype oldtype, MPI_Datatype *newtype));
RECORDER_TYPE(PMPI_Type_extent, int, (MPI_Datatype datatype, MPI_Aint *extent));
RECORDER_TYPE(PMPI_Type_free, int, (MPI_Datatype *datatype));
RECORDER_TYPE(PMPI_Type_hindexed, int, (int count, int *array_of_blocklengths, MPI_Aint *array_of_displacements, MPI_Datatype oldtype, MPI_Datatype *newtype));
RECORDER_TYPE(PMPI_Op_create, int, (MPI_User_function *function, int commute, MPI_Op *op));
RECORDER_TYPE(PMPI_Op_free, int, (MPI_Op *op));
RECORDER_TYPE(PMPI_Reduce, int, (void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm));
RECORDER_TYPE(PMPI_Type_get_envelope, int, (MPI_Datatype datatype, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner));
RECORDER_TYPE(PMPI_Type_size, int, (MPI_Datatype datatype, int *size));

void resolve_mpi_symbols (void)
{
    /*
     * Overloaded functions
     */
    MAP_OR_FAIL(PMPI_File_close);
    MAP_OR_FAIL(PMPI_File_set_size);
    MAP_OR_FAIL(PMPI_File_iread_at);
    MAP_OR_FAIL(PMPI_File_iread);
    MAP_OR_FAIL(PMPI_File_iread_shared);
    MAP_OR_FAIL(PMPI_File_iwrite_at);
    MAP_OR_FAIL(PMPI_File_iwrite);
    MAP_OR_FAIL(PMPI_File_iwrite_shared);
    MAP_OR_FAIL(PMPI_File_open);
    MAP_OR_FAIL(PMPI_File_read_all_begin);
    MAP_OR_FAIL(PMPI_File_read_all);
    MAP_OR_FAIL(PMPI_File_read_at_all_begin);
    MAP_OR_FAIL(PMPI_File_read_at_all);
    MAP_OR_FAIL(PMPI_File_read_at);
    MAP_OR_FAIL(PMPI_File_read);
    MAP_OR_FAIL(PMPI_File_read_ordered_begin);
    MAP_OR_FAIL(PMPI_File_read_ordered);
    MAP_OR_FAIL(PMPI_File_read_shared);
    MAP_OR_FAIL(PMPI_File_set_view);
    MAP_OR_FAIL(PMPI_File_sync);
    MAP_OR_FAIL(PMPI_File_write_all_begin);
    MAP_OR_FAIL(PMPI_File_write_all);
    MAP_OR_FAIL(PMPI_File_write_at_all_begin);
    MAP_OR_FAIL(PMPI_File_write_at_all);
    MAP_OR_FAIL(PMPI_File_write_at);
    MAP_OR_FAIL(PMPI_File_write);
    MAP_OR_FAIL(PMPI_File_write_ordered_begin);
    MAP_OR_FAIL(PMPI_File_write_ordered);
    MAP_OR_FAIL(PMPI_File_write_shared);
    MAP_OR_FAIL(PMPI_Finalize);
    MAP_OR_FAIL(PMPI_Init);
    MAP_OR_FAIL(PMPI_Init_thread);

    /*
     * These function are not intercepted but are used
     * by recorder itself.
     */
    MAP_OR_FAIL(PMPI_Wtime);
    MAP_OR_FAIL(PMPI_Allreduce);
    MAP_OR_FAIL(PMPI_Bcast);
    MAP_OR_FAIL(PMPI_Comm_rank);
    MAP_OR_FAIL(PMPI_Comm_size);
    MAP_OR_FAIL(PMPI_Scan);
    MAP_OR_FAIL(PMPI_Type_commit);
    MAP_OR_FAIL(PMPI_Type_contiguous);
    MAP_OR_FAIL(PMPI_Type_extent);
    MAP_OR_FAIL(PMPI_Type_free);
    MAP_OR_FAIL(PMPI_Type_size);
    MAP_OR_FAIL(PMPI_Type_hindexed);
    MAP_OR_FAIL(PMPI_Op_create);
    MAP_OR_FAIL(PMPI_Op_free);
    MAP_OR_FAIL(PMPI_Reduce);
    MAP_OR_FAIL(PMPI_Type_get_envelope);

    return;
}

#endif

int MPI_Init(int *argc, char ***argv)
{
    int ret;

#ifdef RECORDER_PRELOAD
    resolve_mpi_symbols();
#endif

    ret = RECORDER_MPI_CALL(PMPI_Init)(argc, argv);
    if(ret != MPI_SUCCESS)
    {
        return(ret);
    }

    recorder_mpi_initialize(argc, argv);

    return(ret);
}

int MPI_Init_thread (int *argc, char ***argv, int required, int *provided)
{
    int ret;

    ret = RECORDER_MPI_CALL(PMPI_Init_thread)(argc, argv, required, provided);
    if (ret != MPI_SUCCESS)
    {
        return(ret);
    }

    recorder_mpi_initialize(argc, argv);

    return(ret);
}

int MPI_Finalize(void)
{
    int ret;

	/*
    if(getenv("RECORDER_INTERNAL_TIMING"))
        recorder_shutdown(1);
    else
        recorder_shutdown(0);
	*/

    ret = RECORDER_MPI_CALL(PMPI_Finalize)();
	delete_sc(sc);

    return(ret);
}
