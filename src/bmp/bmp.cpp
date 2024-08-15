
#include "bmp.h"

Bmp24::Bmp24(const std::string& file_name) : bitmap_(1, 1) {
    if (!CheckBmpFormat(file_name)) {
        throw std::runtime_error(file_name + " isn't in .bmp format");
    }

    std::ifstream file(file_name, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error(file_name + " can't be opened.");
    }

    LoadBmpFileHeaders(file, bmp_header_);

    if (!IsValidSignature()) {
        throw std::runtime_error(file_name + " has improper bmp signature, only BM is available.");
    }

    LoadBmpFileHeaders(file, dib_header_);

    if (!IsValidPixelResolution()) {
        throw std::runtime_error(file_name + " has improper width or height.");
    }
    if (!IsValidCompressionMethod()) {
        throw std::runtime_error(file_name + " has improper compression method, only BiRgb is available.");
    }
    if (!IsValidDIBHeaderSize()) {
        throw std::runtime_error(file_name + " has improper specified DIB header size.");
    }
    if (!IsValidColorPaletteSize()) {
        throw std::runtime_error(file_name + " has improper number of colors in palette, must be 0.");
    }

    dib_header_.bitmap_size = dib_header_.height * dib_header_.width;

    file.seekg(bmp_header_.bitmap_offset);
    if (file.fail() || file.bad() || (file.eof() && dib_header_.bitmap_size != 0)) {
        throw std::runtime_error(file_name + " is invalid.");
    }

    bitmap_.SetHeight(static_cast<size_t>(dib_header_.height));
    bitmap_.SetWidth(static_cast<size_t>(dib_header_.width));
    LoadBitmap(file);
    if (file.fail() || file.bad()) {
        throw std::runtime_error(file_name + " is invalid.");
    }
}

bool Bmp24::CheckBmpFormat(const std::string& file_name) const {
    const char* prorep_format = ".bmp";
    if (file_name.size() < 4) {
        return false;
    }
    bool good = true;
    for (size_t i = 0; i < 4; ++i) {
        good = good && std::tolower(file_name[file_name.size() - 4 + i]) == prorep_format[i];
    }
    return good;
}

bool Bmp24::IsValidSignature() const {
    return bmp_header_.signature == ProperSignature;
}

bool Bmp24::IsValidPixelResolution() const {
    return dib_header_.width > 0 && dib_header_.height > 0;
}

bool Bmp24::IsValidCompressionMethod() const {
    return dib_header_.compression_method == BiRgb;
};

bool Bmp24::IsValidDIBHeaderSize() const {
    return dib_header_.header_size == ProperDibheaderSize;
}

bool Bmp24::IsValidColorPaletteSize() const {
    return dib_header_.palette_colors_number == ProperPaletteColorsNumber;
};

bool Bmp24::IsValidColorPlanesNumber() const {
    return dib_header_.color_planes_number == ProperColorplanesNumber;
}

int32_t Bmp24::CalcPadding() const {
    return (4 - 3 * (dib_header_.width % 4) % 4) % 4;
}

void Bmp24::LoadBitmap(std::ifstream& file) {
    int32_t padding = CalcPadding();
    for (size_t i = dib_header_.height - 1; ~i; --i) {
        for (size_t j = 0; j < dib_header_.width; ++j) {
            RGB24& pixel = bitmap_.At(i, j);
            file.read(reinterpret_cast<char*>(&pixel), sizeof(pixel));
        }
        file.seekg(padding, std::ios_base::cur);
    }
}

void Bmp24::WriteBitmap(std::ostream& file) const {
    if (dib_header_.height == 0) {
        return;
    }
    uint32_t padding = CalcPadding();
    for (size_t i = dib_header_.height - 1; ~i; --i) {
        file.write(reinterpret_cast<const char*>(&bitmap_.GetContainer()[i][0]),
                   static_cast<int32_t>(sizeof(RGB24)) * dib_header_.width);
        for (size_t j = 0; j < padding; ++j) {
            file.put(static_cast<uint8_t>(0));
        }
    }
}

void Bmp24::BmpWrite(const std::string& file_name) const {
    if (!CheckBmpFormat(file_name)) {
        throw std::runtime_error(file_name + " isn't in .bmp format");
    }
    std::ofstream file(file_name, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error(file_name + " can't be opened.");
    }
    file.write(reinterpret_cast<const char*>(&bmp_header_), sizeof(BmpHeader));
    file.write(reinterpret_cast<const char*>(&dib_header_), sizeof(DIBHeader));
    WriteBitmap(file);
}

void Bmp24::RecalcHeaders() {
    dib_header_.height = static_cast<int32_t>(bitmap_.GetHeight());
    dib_header_.width = static_cast<int32_t>(bitmap_.GetWidth());
    uint32_t padding = dib_header_.height * CalcPadding();
    dib_header_.bitmap_size = dib_header_.height * dib_header_.width + padding;
    bmp_header_.bmp_file_size = sizeof(BmpHeader) + sizeof(DIBHeader) + dib_header_.bitmap_size;
}

void Bmp24::SwapBitmap(Bitmap<RGB24>& other) {
    bitmap_.Swap(other);
    RecalcHeaders();
}
