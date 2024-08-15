
#include "stuff/reference.h"
#include "bmp/bmp.h"
#include "cmdparser/cmdlineparser.h"
#include "filter/filter_util/filterfactory.h"
#include "filter/filter_util/filterproducers.h"
#include "filter/filters/allfilters.h"

//  #define DEBUG
#ifdef DEBUG
#include "stuff/tests.h"
#endif

//  Над файловой структурой проекта явно еще можно много поработать, но я не уложусь по времени.
int main(int argc, char* argv[]) {
#ifdef DEBUG
    RunTests();
#else
    try {
        CmdLineParser pars(argc, argv);
        if (pars.GetFilters().empty()) {
            PrintHelpReference();
            return 0;
        }
        Bmp24 input(pars.GetInputFile());
        FilterFactory ff;
        //  Здесь добавляется мой кастомный фильтр, он сортирует пиксели по заданной мной заранее лямбде,
        //  неплохой результат выходит, если применить его на Лене (-amuse 1 0).
        //  https://i.imgur.com/MtmQM0W.jpeg
        //  https://i.imgur.com/Rn4Sjuu.jpeg Лена после фильтра.
        //  https://imgur.com/a/HOoN4Wp      ещё один классный пример (-amuse 1 0).
        //  https://imgur.com/a/mPnbdrj      Лена с остальными тремя комбинациями параметров.
        //  Ещё картинка с 4 вариациями параметров этого фильтра в more_amuse_samples.zip.
        ff.SetPFilterProducer("amuse", AmusingFilterProducer);
        FilterPipeline fp = ff.MakeFilterPipeline(pars.GetFilters());
        fp.ApplyOnBmp(input);
        input.BmpWrite(pars.GetOutputFile());
    } catch (std::runtime_error& e) {
        PrintRuntineError(e);
    } catch (std::bad_alloc& e) {
        PrintBadAllocError(e);
    } catch (std::exception& e) {
        PrintUnknownError(e);
    } catch (...) {
        PrintBadUnknownError();
    }
#endif
    return 0;
}
