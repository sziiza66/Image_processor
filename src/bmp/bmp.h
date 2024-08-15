
#ifndef IMG_PROC_BMP_H
#define IMG_PROC_BMP_H

#include <cstdint>
#include <fstream>

#include "../color/color.h"
#include "../color/bitmap/bitmap.h"

struct BmpHeader {
    uint16_t signature;
    uint32_t bmp_file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t bitmap_offset;
} __attribute__((packed));

struct DIBHeader {
    uint32_t header_size;
    int32_t width;
    int32_t height;
    uint16_t color_planes_number;
    uint16_t bits_per_pixel;
    uint32_t compression_method;
    uint32_t bitmap_size;
    int32_t horisontal_resolution;
    int32_t vertical_resolution;
    uint32_t palette_colors_number;
    uint32_t important_colors_number;
} __attribute__((packed));

class Bmp24 {
public:
    using RGB24 = Rgb<uint8_t>;

    explicit Bmp24(const std::string& file_name);

    ~Bmp24() {
    }

    const Bitmap<RGB24>& GetBitmap() {
        return bitmap_;
    }

    void BmpWrite(const std::string& file_name) const;

    void SwapBitmap(Bitmap<RGB24>& other);

private:
    template <typename HeaderType>
    void LoadBmpFileHeaders(std::ifstream& file, HeaderType& header) {
        static_assert(std::is_same_v<HeaderType, DIBHeader> || std::is_same_v<HeaderType, BmpHeader>,
                      "Can only read Bmp or DIB headers");
        file.read(reinterpret_cast<char*>(&header), sizeof(HeaderType));
    }

    int32_t CalcPadding() const;
    void LoadBitmap(std::ifstream& file);
    void WriteBitmap(std::ostream& file) const;
    void RecalcHeaders();

    bool CheckBmpFormat(const std::string& file_name) const;
    bool IsValidSignature() const;
    bool IsValidDIBHeaderSize() const;
    bool IsValidPixelResolution() const;
    bool IsValidCompressionMethod() const;
    bool IsValidColorPaletteSize() const;
    bool IsValidColorPlanesNumber() const;

    BmpHeader bmp_header_;
    DIBHeader dib_header_;
    Bitmap<RGB24> bitmap_;

private:
    constexpr static uint16_t BM = 19778;
    constexpr static uint16_t ProperSignature = BM;
    constexpr static uint32_t ProperDibheaderSize = 40;
    constexpr static uint16_t ProperColorplanesNumber = 1;
    constexpr static uint32_t BiRgb = 0;
    constexpr static uint32_t ProperPaletteColorsNumber = 0;
};

#endif  // IMG_PROC_BMP_H
