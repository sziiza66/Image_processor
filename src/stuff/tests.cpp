
#include "tests.h"

#include <stdexcept>
#include <iostream>
#include <cassert>

#include "../stuff/reference.h"
#include "../bmp/bmp.h"
#include "../cmdparser/cmdlineparser.h"
#include "../filter/filter_util/filterfactory.h"
#include "../filter/filter_util/filterproducers.h"
#include "../filter/filters/allfilters.h"

void TestDescriptor() {
    using namespace std::literals;
    FilterDescriptor gauss_descr("gauss"sv, {"1.075"sv});
    FilterDescriptor gs_descr("gs"sv);
    FilterDescriptor crops_descr("crop", {"800", "600"});
}

void TestParser() {
    constexpr int Argc = 8;
    const char* cmd[]{static_cast<const char*>("prog_name"), static_cast<const char*>("in"),
                      static_cast<const char*>("out"),       static_cast<const char*>("-filter1"),
                      static_cast<const char*>("param1"),    static_cast<const char*>("param2"),
                      static_cast<const char*>("-filter2"),  static_cast<const char*>("-filter3")};
    CmdLineParser(Argc, cmd);
}

void TestSaveBmp() {
    char file_name[] = "../test_script/data/flag.bmp";
    Bmp24 image(file_name);
    image.BmpWrite("test_save.bmp");
}

void TestCrop() {
    constexpr size_t Big1 = 1000000;
    constexpr size_t Big2 = 100000000;
    char file_name[] = "../test_script/data/flag.bmp";
    Bmp24 image(file_name);
    CropFilter crop_filter(Big1, Big2);
    crop_filter.ApplyOnBmp(image);
    image.BmpWrite("test_crop.bmp");
}

void TestGrayscale() {
    char file_name[] = "../test_script/data/lenna.bmp";
    Bmp24 image(file_name);
    GrayscaleFilter gs_filter;
    gs_filter.ApplyOnBmp(image);
    image.BmpWrite("test_gs.bmp");
}

void TestNegative() {
    char file_name[] = "../test_script/data/lenna.bmp";
    Bmp24 image(file_name);
    NegativeFilter neg_filter;
    neg_filter.ApplyOnBmp(image);
    image.BmpWrite("test_neg.bmp");
}

void TestMatrix() {
    constexpr int32_t Five = 5;  // Ну это несерьёзно.
    char file_name[] = "../test_script/data/lenna.bmp";
    Bmp24 image(file_name);
    std::vector<std::vector<int32_t>> matrix = {{0, -1, 0}, {-1, Five, -1}, {0, -1, 0}};
    MatrixFilter mat_filter(matrix);
    mat_filter.ApplyOnBmp(image);
    image.BmpWrite("test_matrix.bmp");
}

void TestSharp() {
    char file_name[] = "../test_script/data/lenna.bmp";
    Bmp24 image(file_name);
    SharpeningFilter sh_filter;
    sh_filter.ApplyOnBmp(image);
    image.BmpWrite("test_sharp.bmp");
    sh_filter.ApplyOnBmp(image);
    image.BmpWrite("test_sharp_sharp.bmp");
}

void TestEdge() {
    constexpr int FilterParam = 10;
    char file_name[] = "../test_script/data/lenna.bmp";
    Bmp24 image(file_name);
    EdgeDetectionFilter edge_filter(FilterParam);
    edge_filter.ApplyOnBmp(image);
    image.BmpWrite("test_edge.bmp");
    edge_filter.ApplyOnBmp(image);
    image.BmpWrite("test_edge_egde.bmp");
}

void TestBlur() {
    constexpr double FilterParam1 = 7.5;
    constexpr double FilterParam2 = 3;
    char file_name[] = "../test_script/data/lenna.bmp";
    Bmp24 image(file_name);
    GaussianBlurFilter blur_filter(FilterParam1);
    blur_filter.ApplyOnBmp(image);
    image.BmpWrite("test_blur.bmp");
    GaussianBlurFilter blur_filter2(FilterParam2);
    blur_filter2.ApplyOnBmp(image);
    image.BmpWrite("test_blur_blur.bmp");
}

void TestAmusing() {
    char file_name[] = "../test_script/data/lenna.bmp";
    Bmp24 image(file_name);
    AmusingFilter am_filter(true, false);
    am_filter.ApplyOnBmp(image);
    image.BmpWrite("test_amusing.bmp");
}

void TestAmusingCmd() {
    try {
        constexpr int Argc = 6;
        const char* argv[]{static_cast<const char*>("image_processor.exe"),
                           static_cast<const char*>("city_beauty.bmp"),
                           static_cast<const char*>("city_beauty_amused.bmp"),
                           static_cast<const char*>("-amuse"),
                           static_cast<const char*>("1"),
                           static_cast<const char*>("0")};
        CmdLineParser pars(Argc, argv);
        if (pars.GetFilters().empty()) {
            PrintHelpReference();
            return;
        }
        Bmp24 input(pars.GetInputFile());
        FilterFactory ff;
        ff.SetPFilterProducer(std::string("amuse"), AmusingFilterProducer);
        FilterPipeline fp = ff.MakeFilterPipeline(pars.GetFilters());
        fp.ApplyOnBmp(input);
        input.BmpWrite(pars.GetOutputFile());
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
    } catch (...) {
        std::cerr << "Unknown\n";
    }
}

void TestGarbageInput1() {
    try {
        constexpr int Argc = 6;
        const char* argv[]{static_cast<const char*>("image_processor.exe"),
                           static_cast<const char*>("fg"),
                           static_cast<const char*>("fasafsdap[lf"),
                           static_cast<const char*>("aslpdf"),
                           static_cast<const char*>("asdkof"),
                           static_cast<const char*>("a\\")};
        CmdLineParser pars(Argc, argv);
        if (pars.GetFilters().empty()) {
            PrintHelpReference();
            return;
        }
        Bmp24 input(pars.GetInputFile());
        FilterFactory ff;
        ff.SetPFilterProducer(std::string("amuse"), AmusingFilterProducer);
        FilterPipeline fp = ff.MakeFilterPipeline(pars.GetFilters());
        fp.ApplyOnBmp(input);
        input.BmpWrite(pars.GetOutputFile());
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
    } catch (...) {
        std::cerr << "Unknown\n";
    }
}

void TestGarbageInput2() {
    try {
        constexpr int Argc = 2;
        const char* argv[]{static_cast<const char*>("image_processor.exe"), static_cast<const char*>("fg")};
        CmdLineParser pars(Argc, argv);
        if (pars.GetFilters().empty()) {
            PrintHelpReference();
            return;
        }
        Bmp24 input(pars.GetInputFile());
        FilterFactory ff;
        ff.SetPFilterProducer(std::string("amuse"), AmusingFilterProducer);
        FilterPipeline fp = ff.MakeFilterPipeline(pars.GetFilters());
        fp.ApplyOnBmp(input);
        input.BmpWrite(pars.GetOutputFile());
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
    } catch (...) {
        std::cerr << "Unknown\n";
    }
}

void RunTests() {
    TestSaveBmp();
    TestCrop();
    TestGrayscale();
    TestNegative();
    TestMatrix();
    TestSharp();
    TestEdge();
    TestBlur();
    TestAmusing();
    TestAmusingCmd();
    TestGarbageInput1();
    TestGarbageInput2();
}
