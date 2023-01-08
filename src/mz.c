#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <binary.h>
#include <mz.h>

void mz_move_to_packheader(FILE *file)
{
    /* check the mz magic header */
    char mz_magic[2];
    fread(&mz_magic, sizeof(char), 2, file);
    mz_magic[2] = '\0';

    assert(strcmp(mz_magic, "MZ") == 0);

    /* moving the pe header */
    fseek(file, 0x3c, SEEK_SET);
    uint32_t offset = get_uint(file);
    fseek(file, offset, SEEK_SET);

    /* check the pe magic header */
    char pe_magic[4];
    fread(&pe_magic, sizeof(pe_magic), 1, file);
    assert(strcmp(pe_magic, "PE\0\0") == 0);

    /* reading the section count */
    fseek(file, 0x2, SEEK_CUR);
    uint16_t section_count = get_ushort(file);
    fseek(file, 0x10, SEEK_CUR);

    /* seek tot first section table entry */
    int optional_header = 0x60;
    int data_directory = 0x80;
    fseek(file, optional_header + data_directory, SEEK_CUR);

    /* getting the position */
    int position;

    for (int index = 0; index < section_count; index++)
    {
        int start = ftell(file);
        char *name = get_string(file);

        if (strcmp(name, ".extra") == 0)
        {
            fseek(file, start + 0x14, SEEK_SET);
            position = get_uint(file);

            break;
        }

        if (index >= section_count - 1)
        {
            fseek(file, start + 0x10, SEEK_SET);

            uint32_t size = get_uint(file);
            uint32_t address = get_uint(file);

            position = size + address;
            break;
        }

        fseek(file, start + 0x28, SEEK_SET);
    }

    fseek(file, position, SEEK_SET);
}

mz_t mz_read(FILE *file)
{
    mz_t mz_result;

    /* move to the packheader */
    mz_move_to_packheader(file);
    mz_result.data_position = ftell(file);

    return mz_result;
}
