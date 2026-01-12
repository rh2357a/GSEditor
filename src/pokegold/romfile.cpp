#include "romfile.h"

#include "lib/lzcomp.h"
#include "utils.h"

void pokegold::romfile::open(const std::filesystem::path &filepath)
{
    path = filepath;

    const auto filename = filepath.stem().string();
    save_path = filepath.parent_path() / (filename + ".sav");
    build_data_path = filepath.parent_path() / (filename + ".gsb");

    workspace_path = utils::files::get_app_data_path() / "workspaces" / utils::crypto::hash(filepath.string());

    const auto bytes = utils::files::read_bytes_from_file(path);
    data.insert(data.end(), bytes.begin(), bytes.end());

    is_opened = true;
}

void pokegold::romfile::close()
{
    path = "";
    save_path = "";
    build_data_path = "";

    data.clear();

    is_opened = false;
    is_changed = false;
}

u8 pokegold::romfile::get_byte(size_t addr)
{
    return data[addr];
}

std::vector<u8> pokegold::romfile::get_bytes(size_t addr, size_t len)
{
    if (len == 0 || addr >= data.size() || len > data.size() - addr)
        return {};

    std::vector<u8> result;
    for (size_t i = 0; i < len; i++)
        result.push_back(data[addr + i]);

    return result;
}

std::vector<u8> pokegold::romfile::get_bytes_until(size_t addr, std::function<bool(size_t, u8)> predicate, bool include_end)
{
    if (addr >= data.size())
        return {};

    std::vector<u8> result;
    size_t i = 0;
    while (addr + i < data.size())
    {
        u8 b = data[addr + i];
        if (predicate(i, b))
        {
            if (include_end)
                result.push_back(b);
            break;
        }

        result.push_back(b);
        i++;
    }

    return result;
}

size_t pokegold::romfile::calc_lz_size(size_t offset, size_t buffer_size)
{
    if (buffer_size == 0 || offset >= data.size() || buffer_size > data.size() - offset)
        return 0;

    std::span<const u8> buf(data.data() + offset, buffer_size);
    return lzcomp::scan_lz_size(buf);
}

size_t pokegold::romfile::read_lz_decompressed(std::span<u8> dst, size_t offset, size_t size)
{
    if (size == 0 || offset >= data.size() || size > data.size() - offset)
        return 0;

    return lzcomp::uncompress(dst, data, offset, size);
}

void pokegold::romfile::set_byte(size_t addr, u8 byte)
{
    data[addr] = byte;
}

void pokegold::romfile::set_bytes(size_t addr, const std::vector<u8> &bytes)
{
    if (addr >= data.size() || bytes.size() > data.size() - addr)
        return;

    for (size_t i = 0; i < bytes.size(); i++)
        data[addr + i] = bytes[i];
}

void pokegold::romfile::fill_bytes(u8 byte, size_t addr, size_t len)
{
    if (addr >= data.size() || len > data.size() - addr)
        return;

    for (size_t i = 0; i < len; i++)
        data[addr + i] = byte;
}
