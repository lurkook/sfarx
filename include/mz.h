#ifndef MZ_H_
#define MZ_H_

typedef struct mz
{
    int data_position;
} mz_t;

void mz_move_to_packheader(FILE *file);
mz_t mz_read(FILE *file);

#endif