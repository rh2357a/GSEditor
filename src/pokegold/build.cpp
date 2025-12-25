#include "pokegold.h"
#include "utils.h"
#include <filesystem>

std::vector<u8> pokegold::build()
{
    const auto real_workdir = workspace_path / "workspace";
    const auto base_path = real_workdir / "base.bin";
    const auto target_path = real_workdir / "target.bin";

    debug_log("pokegold::build", "cleanup (path=\"{}\")", real_workdir.string());
    std::filesystem::remove_all(real_workdir);
    std::filesystem::create_directories(real_workdir);

    debug_log("pokegold::build", "copy baserom to workspace dir");
    utils::files::write_bytes_to_file(base_path, rom.data());

    const auto result = utils::files::read_bytes_from_file(target_path);

    // cleanup
#ifdef RELEASE
    std::filesystem::remove_all(real_workdir);
#endif

    return result;
}
