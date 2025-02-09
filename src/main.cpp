#include "PlaceInRed/PlaceInRed.h"
#include "Scripts/Papyrus.h"

void InitializeLog()
{
	auto path = logger::log_directory();
	const auto gamepath = REL::Module::IsVR() ? "Fallout4VR/F4SE" : "Fallout4/F4SE";
	if (!path.value().generic_string().ends_with(gamepath)) {
		// handle bug where game directory is missing
		path = path.value().parent_path().append(gamepath);
	}

	*path /= fmt::format("{}.log"sv, "PlaceInRedVR"sv);
	auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);

	const auto level = spdlog::level::trace;

	auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));
	log->set_level(level);
	log->flush_on(level);

	spdlog::set_default_logger(std::move(log));
	spdlog::set_pattern("[%Y-%m-%d %T.%e][%-16s:%-4#][%L]: %v"s);
}

extern "C" DLLEXPORT bool F4SEAPI F4SEPlugin_Query(const F4SE::QueryInterface* a_skse, F4SE::PluginInfo* a_info)
{
	a_info->infoVersion = F4SE::PluginInfo::kVersion;
	a_info->name = Version::PROJECT.data();
	a_info->version = Version::MAJOR;

	if (a_skse->IsEditor()) {
		logger::critical("Loaded in editor, marking as incompatible"sv);
		return false;
	}

	const auto ver = a_skse->RuntimeVersion();
	if (ver < (REL::Module::IsF4() ? F4SE::RUNTIME_LATEST : F4SE::RUNTIME_LATEST_VR)) {
		logger::critical(FMT_STRING("Unsupported runtime version {}"), ver.string());
		return false;
	}

	return true;
}

extern "C" DLLEXPORT bool F4SEAPI F4SEPlugin_Load(const F4SE::LoadInterface* a_f4se)
{
	InitializeLog();
	Settings::load();
	F4SE::Init(a_f4se, false);
	F4SE::GetPapyrusInterface()->Register(Papyrus::RegisterFunctions);

	logger::info("Place In Red For VR v{}.{}.{} {} {} is loading"sv, Version::MAJOR, Version::MINOR, Version::PATCH, __DATE__, __TIME__);
	const auto runtimeVer = REL::Module::get().version();
	logger::info("Fallout 4 v{}.{}.{}"sv, runtimeVer[0], runtimeVer[1], runtimeVer[2]);

	PlaceInRed::EnableInitialDefault();

	logger::info("Place In Red For VR loaded"sv);
	return true;
}

