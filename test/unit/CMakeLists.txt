add_executable(mediaelch_unit)

target_sources(
  mediaelch_unit
  PRIVATE
    main.cpp
    data/testImdbId.cpp
    data/testTmdbId.cpp
    data/testCertification.cpp
    globals/testVersionInfo.cpp
    globals/testTime.cpp
    movie/testMovieFileSearcher.cpp
    settings/testAdvancedSettings.cpp
    tv_shows/testTvShowFileSearcher.cpp
    tv_shows/testTvDbId.cpp
)

target_link_libraries(
  mediaelch_unit PRIVATE libmediaelch libmediaelch_testhelpers
)

generate_coverage_report(mediaelch_unit)
catch_discover_tests(mediaelch_unit)
mediaelch_post_target_defaults(mediaelch_unit)

# Convenience unit test target with color output; does not use CTest
add_custom_target(
  unit_test COMMAND $<TARGET_FILE:mediaelch_unit> --use-colour yes
)
