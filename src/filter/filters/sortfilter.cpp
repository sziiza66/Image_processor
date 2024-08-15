
#include "sortfilter.h"

void SortFilter::ApplyOnBmp(Bmp24& image) const {
    Bitmap<RGB24> buffer(vertical_ ? image.GetBitmap().GetRotated() : image.GetBitmap());
    buffer.SortHorisontally(sort_func_, rev_);
    if (vertical_) {
        buffer = buffer.GetRotated();
    }
    image.SwapBitmap(buffer);
}
