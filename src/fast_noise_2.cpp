#include "fast_noise_2.h"
#include <godot_cpp/variant/variant.hpp>

namespace zylann {

FastNoise2::FastNoise2() {
	// Setup default
	update_generator();
}

void FastNoise2::set_encoded_node_tree(godot::String data) {
	if (data != _last_set_encoded_node_tree) {
		_last_set_encoded_node_tree = data;
		emit_changed();
	}
}

bool FastNoise2::is_valid() const {
	return _generator.get() != nullptr;
}

godot::String FastNoise2::get_encoded_node_tree() const {
	// There is no way to get back an encoded node tree from `FastNoise::SmartNode<>`
	return _last_set_encoded_node_tree;
}

FastNoise2::SIMDLevel FastNoise2::get_simd_level() const {
	ERR_FAIL_COND_V(!is_valid(), SIMD_NULL);
	return SIMDLevel(_generator->GetSIMDLevel());
}

const char *FastNoise2::get_simd_level_name_c_str(SIMDLevel level) {
	switch (level) {
		case SIMD_NULL:
			return "Null";
		case SIMD_SCALAR:
			return "Scalar";
		case SIMD_SSE:
			return "SSE";
		case SIMD_SSE2:
			return "SSE2";
		case SIMD_SSE3:
			return "SSE3";
		case SIMD_SSE41:
			return "SSE41";
		case SIMD_SSE42:
			return "SSE42";
		case SIMD_AVX:
			return "AVX";
		case SIMD_AVX2:
			return "AVX2";
		case SIMD_AVX512:
			return "AVX512";
		case SIMD_NEON:
			return "NEON";
		default:
			ERR_PRINT(godot::vformat("Unknown SIMD level %d", level));
			return "Error";
	}
}

godot::String FastNoise2::get_simd_level_name(SIMDLevel level) {
	return get_simd_level_name_c_str(level);
}

void FastNoise2::set_seed(int seed) {
	if (_seed == seed) {
		return;
	}
	_seed = seed;
	emit_changed();
}

int FastNoise2::get_seed() const {
	return _seed;
}

void FastNoise2::set_noise_type(NoiseType type) {
	if (_noise_type == type) {
		return;
	}
	_noise_type = type;
	emit_changed();
}

FastNoise2::NoiseType FastNoise2::get_noise_type() const {
	return _noise_type;
}

void FastNoise2::set_period(float p) {
	if (p < 0.0001f) {
		p = 0.0001f;
	}
	if (_period == p) {
		return;
	}
	_period = p;
	emit_changed();
}

float FastNoise2::get_period() const {
	return _period;
}

void FastNoise2::set_fractal_octaves(int octaves) {
	ERR_FAIL_COND(octaves <= 0);
	if (octaves > MAX_OCTAVES) {
		octaves = MAX_OCTAVES;
	}
	if (_fractal_octaves == octaves) {
		return;
	}
	_fractal_octaves = octaves;
	emit_changed();
}

void FastNoise2::set_fractal_type(FractalType type) {
	if (_fractal_type == type) {
		return;
	}
	_fractal_type = type;
	emit_changed();
}

FastNoise2::FractalType FastNoise2::get_fractal_type() const {
	return _fractal_type;
}

int FastNoise2::get_fractal_octaves() const {
	return _fractal_octaves;
}

void FastNoise2::set_fractal_lacunarity(float lacunarity) {
	if (_fractal_lacunarity == lacunarity) {
		return;
	}
	_fractal_lacunarity = lacunarity;
	emit_changed();
}

float FastNoise2::get_fractal_lacunarity() const {
	return _fractal_lacunarity;
}

void FastNoise2::set_fractal_gain(float gain) {
	if (_fractal_gain == gain) {
		return;
	}
	_fractal_gain = gain;
	emit_changed();
}

float FastNoise2::get_fractal_gain() const {
	return _fractal_gain;
}

void FastNoise2::set_fractal_ping_pong_strength(float s) {
	if (_fractal_ping_pong_strength == s) {
		return;
	}
	_fractal_ping_pong_strength = s;
	emit_changed();
}

float FastNoise2::get_fractal_ping_pong_strength() const {
	return _fractal_ping_pong_strength;
}

void FastNoise2::set_terrace_enabled(bool enable) {
	if (enable == _terrace_enabled) {
		return;
	}
	_terrace_enabled = enable;
	emit_changed();
}

bool FastNoise2::is_terrace_enabled() const {
	return _terrace_enabled;
}

void FastNoise2::set_terrace_multiplier(float m) {
	const float clamped_multiplier = std::max(m, 0.f);
	if (clamped_multiplier == _terrace_multiplier) {
		return;
	}
	_terrace_multiplier = clamped_multiplier;
	emit_changed();
}

float FastNoise2::get_terrace_multiplier() const {
	return _terrace_multiplier;
}

void FastNoise2::set_terrace_smoothness(float s) {
	const float clamped_smoothness = std::max(s, 0.f);
	if (_terrace_smoothness == clamped_smoothness) {
		return;
	}
	_terrace_smoothness = clamped_smoothness;
	emit_changed();
}

float FastNoise2::get_terrace_smoothness() const {
	return _terrace_smoothness;
}

void FastNoise2::set_remap_enabled(bool enabled) {
	if (enabled != _remap_enabled) {
		_remap_enabled = enabled;
		emit_changed();
	}
}

bool FastNoise2::is_remap_enabled() const {
	return _remap_enabled;
}

void FastNoise2::set_remap_input_min(float min_value) {
	if (min_value != _remap_src_min) {
		_remap_src_min = min_value;
		emit_changed();
	}
}

float FastNoise2::get_remap_input_min() const {
	return _remap_src_min;
}

void FastNoise2::set_remap_input_max(float max_value) {
	if (max_value != _remap_src_max) {
		_remap_src_max = max_value;
		emit_changed();
	}
}

float FastNoise2::get_remap_input_max() const {
	return _remap_src_max;
}

void FastNoise2::set_remap_output_min(float min_value) {
	if (min_value != _remap_dst_min) {
		_remap_dst_min = min_value;
		emit_changed();
	}
}

float FastNoise2::get_remap_output_min() const {
	return _remap_dst_min;
}

void FastNoise2::set_remap_output_max(float max_value) {
	if (max_value != _remap_dst_max) {
		_remap_dst_max = max_value;
		emit_changed();
	}
}

float FastNoise2::get_remap_output_max() const {
	return _remap_dst_max;
}

void FastNoise2::set_cellular_distance_function(CellularDistanceFunction cdf) {
	if (cdf == _cellular_distance_function) {
		return;
	}
	_cellular_distance_function = cdf;
	emit_changed();
}

FastNoise2::CellularDistanceFunction FastNoise2::get_cellular_distance_function() const {
	return _cellular_distance_function;
}

void FastNoise2::set_cellular_return_type(CellularReturnType rt) {
	if (_cellular_return_type == rt) {
		return;
	}
	_cellular_return_type = rt;
	emit_changed();
}

FastNoise2::CellularReturnType FastNoise2::get_cellular_return_type() const {
	return _cellular_return_type;
}

void FastNoise2::set_cellular_jitter(float jitter) {
	jitter = std::clamp(jitter, 0.f, 1.f);
	if (_cellular_jitter == jitter) {
		return;
	}
	_cellular_jitter = jitter;
	emit_changed();
}

float FastNoise2::get_cellular_jitter() const {
	return _cellular_jitter;
}

float FastNoise2::get_noise_2d_single(godot::Vector2 pos) const {
	ERR_FAIL_COND_V(!is_valid(), 0.0);
	return _generator->GenSingle2D(pos.x, pos.y, _seed);
}

float FastNoise2::get_noise_3d_single(godot::Vector3 pos) const {
	ERR_FAIL_COND_V(!is_valid(), 0.0);
	return _generator->GenSingle3D(pos.x, pos.y, pos.z, _seed);
}

void FastNoise2::get_noise_2d_series(Span<const float> src_x, Span<const float> src_y, Span<float> dst) const {
	ERR_FAIL_COND(!is_valid());
	ERR_FAIL_COND(src_x.size() != src_y.size() || src_x.size() != dst.size());
	if (src_x.size() < MIN_BUFFER_SIZE) {
		// Using backing arrays for input buffers, because SIMD needs to read multiple values. This might make
		// single-reads a bit slower, but in that case performance likely doesn't matter anyways
		std::array<float, MIN_BUFFER_SIZE> x;
		std::array<float, MIN_BUFFER_SIZE> y;
		std::array<float, MIN_BUFFER_SIZE> n;
		// We should not need to spend time initializing these arrays because they are just backing memory. We write
		// over them and FN2 will write over the result anyways. But if we don't do this, GCC is not happy because all
		// warnings are enabled and treated as errors...
		for (float &v : x) {
			v = 0.f;
		}
		for (float &v : y) {
			v = 0.f;
		}
		for (float &v : n) {
			v = 0.f;
		}
		for (unsigned int i = 0; i < src_x.size(); ++i) {
			x[i] = src_x[i];
		}
		for (unsigned int i = 0; i < src_y.size(); ++i) {
			y[i] = src_y[i];
		}
		// TODO Need to update FastNoise2.
		// Using a destination buffer smaller than SIMD level is not supposed to break, but it crashes. Using a backing
		// array too as workaround.
		_generator->GenPositionArray2D(n.data(), n.size(), x.data(), y.data(), 0, 0, _seed);
		for (unsigned int i = 0; i < dst.size(); ++i) {
			dst[i] = n[i];
		}
	} else {
		_generator->GenPositionArray2D(dst.data(), dst.size(), src_x.data(), src_y.data(), 0, 0, _seed);
	}
}

void FastNoise2::get_noise_3d_series(
		Span<const float> src_x,
		Span<const float> src_y,
		Span<const float> src_z,
		Span<float> dst
) const {
	ERR_FAIL_COND(!is_valid());
	ERR_FAIL_COND(src_x.size() != src_y.size() || src_x.size() != src_z.size() || src_x.size() != dst.size());
	if (src_x.size() < MIN_BUFFER_SIZE) {
		std::array<float, MIN_BUFFER_SIZE> x;
		std::array<float, MIN_BUFFER_SIZE> y;
		std::array<float, MIN_BUFFER_SIZE> z;
		std::array<float, MIN_BUFFER_SIZE> n;
		// We should not need to spend time initializing these arrays because they are just backing memory. We write
		// over them and FN2 will write over the result anyways. But if we don't do this, GCC is not happy because all
		// warnings are enabled and treated as errors...
		for (float &v : x) {
			v = 0.f;
		}
		for (float &v : y) {
			v = 0.f;
		}
		for (float &v : z) {
			v = 0.f;
		}
		for (float &v : n) {
			v = 0.f;
		}
		for (unsigned int i = 0; i < src_x.size(); ++i) {
			x[i] = src_x[i];
		}
		for (unsigned int i = 0; i < src_y.size(); ++i) {
			y[i] = src_y[i];
		}
		for (unsigned int i = 0; i < src_z.size(); ++i) {
			z[i] = src_z[i];
		}
		// TODO Need to update FastNoise2.
		// Using a destination buffer smaller than SIMD level is not supposed to break, but it crashes. Using a backing
		// array too as workaround.
		_generator->GenPositionArray3D(n.data(), n.size(), x.data(), y.data(), z.data(), 0, 0, 0, _seed);
		for (unsigned int i = 0; i < dst.size(); ++i) {
			dst[i] = n[i];
		}
	} else {
		_generator->GenPositionArray3D(
				dst.data(), dst.size(), src_x.data(), src_y.data(), src_z.data(), 0, 0, 0, _seed
		);
	}
}

Interval FastNoise2::get_noise_2d_grid(godot::Vector2 origin, godot::Vector2i size, Span<float> dst) const {
	ERR_FAIL_COND_V(!is_valid(), Interval());
	ERR_FAIL_COND_V(size.x < 0 || size.y < 0, Interval());
	ERR_FAIL_COND_V(dst.size() != size_t(size.x) * size_t(size.y), Interval());
	const FastNoise::OutputMinMax range =
			_generator->GenUniformGrid2D(dst.data(), origin.x, origin.y, size.x, size.y, 1.f, _seed);
	return Interval{ range.min, range.max };
}

Interval FastNoise2::get_noise_3d_grid(godot::Vector3 origin, godot::Vector3i size, Span<float> dst) const {
	ERR_FAIL_COND_V(!is_valid(), Interval());
	ERR_FAIL_COND_V(size.x <= 0, Interval());
	ERR_FAIL_COND_V(size.y <= 0, Interval());
	ERR_FAIL_COND_V(size.z <= 0, Interval());
	ERR_FAIL_COND_V(dst.size() != size_t(size.x) * size_t(size.y) * size_t(size.z), Interval());
	const FastNoise::OutputMinMax range =
			_generator->GenUniformGrid3D(dst.data(), origin.x, origin.y, origin.z, size.x, size.y, size.z, 1.f, _seed);
	return Interval{ range.min, range.max };
}

Interval FastNoise2::get_noise_2d_grid_tileable(godot::Vector2i size, Span<float> dst) const {
	ERR_FAIL_COND_V(!is_valid(), Interval());
	ERR_FAIL_COND_V(size.x < 0 || size.y < 0, Interval());
	ERR_FAIL_COND_V(dst.size() != size_t(size.x) * size_t(size.y), Interval());
	const FastNoise::OutputMinMax range = _generator->GenTileable2D(dst.data(), size.x, size.y, 1.f, _seed);
	return Interval{ range.min, range.max };
}

void FastNoise2::update_generator() {
	if (_noise_type == TYPE_ENCODED_NODE_TREE) {
		godot::CharString cs = _last_set_encoded_node_tree.utf8();
		// TODO FastNoise2 crashes if given an empty string.
		ERR_FAIL_COND_MSG(cs.length() == 0, "Encoded node tree is empty.");
		_generator = FastNoise::NewFromEncodedNodeTree(cs.get_data());
		ERR_FAIL_COND_MSG(!is_valid(), "Encoded node tree is invalid.");
		// TODO Maybe apply period modifier here?
		// NoiseTool assumes we scale input coordinates so typical noise made in there has period 1...
		return;
	}

	FastNoise::SmartNode<FastNoise::Generator> noise_node;
	switch (_noise_type) {
		case TYPE_OPEN_SIMPLEX_2:
			noise_node = FastNoise::New<FastNoise::OpenSimplex2>();
			break;

		case TYPE_SIMPLEX:
			noise_node = FastNoise::New<FastNoise::Simplex>();
			break;

		case TYPE_PERLIN:
			noise_node = FastNoise::New<FastNoise::Perlin>();
			break;

		case TYPE_VALUE:
			noise_node = FastNoise::New<FastNoise::Value>();
			break;

		case TYPE_CELLULAR: {
			FastNoise::SmartNode<FastNoise::CellularDistance> cd = FastNoise::New<FastNoise::CellularDistance>();
			cd->SetDistanceFunction(FastNoise::DistanceFunction(_cellular_distance_function));
			cd->SetReturnType(FastNoise::CellularDistance::ReturnType(_cellular_return_type));
			cd->SetJitterModifier(_cellular_jitter);
			noise_node = cd;
		} break;

		default:
			ERR_PRINT(godot::vformat("Unknown noise type %d", _noise_type));
			return;
	}

	ERR_FAIL_COND(noise_node.get() == nullptr);
	FastNoise::SmartNode<> generator_node = noise_node;

	if (_period != 1.f) {
		FastNoise::SmartNode<FastNoise::DomainScale> scale_node = FastNoise::New<FastNoise::DomainScale>();
		scale_node->SetScale(1.f / _period);
		scale_node->SetSource(generator_node);
		generator_node = scale_node;
	}

	FastNoise::SmartNode<FastNoise::Fractal<>> fractal_node;
	switch (_fractal_type) {
		case FRACTAL_NONE:
			break;

		case FRACTAL_FBM:
			fractal_node = FastNoise::New<FastNoise::FractalFBm>();
			break;

		case FRACTAL_PING_PONG: {
			FastNoise::SmartNode<FastNoise::FractalPingPong> pp_node = FastNoise::New<FastNoise::FractalPingPong>();
			pp_node->SetPingPongStrength(_fractal_ping_pong_strength);
			fractal_node = pp_node;
		} break;

		case FRACTAL_RIDGED:
			fractal_node = FastNoise::New<FastNoise::FractalRidged>();
			break;

		default:
			ERR_PRINT(godot::vformat("Unknown fractal type %d", _fractal_type));
			return;
	}

	if (fractal_node) {
		fractal_node->SetGain(_fractal_gain);
		fractal_node->SetLacunarity(_fractal_lacunarity);
		fractal_node->SetOctaveCount(_fractal_octaves);
		// fractal_node->SetWeightedStrength(_fractal_weighted_strength);
		fractal_node->SetSource(generator_node);
		generator_node = fractal_node;
	}

	if (_terrace_enabled) {
		FastNoise::SmartNode<FastNoise::Terrace> terrace_node = FastNoise::New<FastNoise::Terrace>();
		terrace_node->SetMultiplier(_terrace_multiplier);
		terrace_node->SetSmoothness(_terrace_smoothness);
		terrace_node->SetSource(generator_node);
		generator_node = terrace_node;
	}

	if (_remap_enabled) {
		FastNoise::SmartNode<FastNoise::Remap> remap_node = FastNoise::New<FastNoise::Remap>();
		remap_node->SetRemap(_remap_src_min, _remap_src_max, _remap_dst_min, _remap_dst_max);
		remap_node->SetSource(generator_node);
		generator_node = remap_node;
	}

	ERR_FAIL_COND(generator_node.get() == nullptr);
	_generator = generator_node;
}

// math::Interval FastNoise2::get_estimated_output_range() const {
// 	// TODO Optimize: better range analysis on FastNoise2
// 	// Most noises should have known bounds like FastNoiseLite, but the node-graph nature of this library
// 	// can make it difficult to calculate. Would be nice if the library could provide that out of the box.
// 	if (is_remap_enabled()) {
// 		return math::Interval::from_unordered_values(get_remap_output_min(), get_remap_output_max());
// 	} else {
// 		return math::Interval(-1.f, 1.f);
// 	}
// }

godot::String FastNoise2::_b_get_simd_level_name(SIMDLevel level) {
	return get_simd_level_name(level);
}

void normalize(Span<float> values, const Interval range) {
	if (std::abs(range.max - range.min) < 0.00001f) {
		for (float &v : values) {
			v = std::clamp(v, 0.f, 1.f);
		}
	} else {
		const float k = 1.f / (range.max - range.min);
		for (float &v : values) {
			v = std::clamp((v - range.min) * k, 0.f, 1.f);
		}
	}
}

godot::PackedByteArray convert_f32_snorm_to_u8_packed_byte_array(Span<const float> src) {
	godot::PackedByteArray bytes;
	bytes.resize(src.size());
	Span<uint8_t> bytes_s(bytes.ptrw(), bytes.size());
	for (size_t i = 0; i < src.size(); ++i) {
		const float n = src[i];
		bytes_s[i] = std::clamp(static_cast<int>((n * 0.5f + 0.5f) * 255.f), 0, 255);
	}
	return bytes;
}

godot::PackedByteArray reinterpret_f32_to_packed_byte_array(Span<const float> src) {
	godot::PackedByteArray bytes;
	bytes.resize(src.size() * sizeof(float));
	memcpy(bytes.ptrw(), src.data(), src.size() * sizeof(float));
	return bytes;
}

godot::Ref<godot::Image> FastNoise2::get_image_with_options_internal(
		const godot::Vector2i p_size,
		const ImageOptions p_options
) const {
	ERR_FAIL_COND_V(p_size.x < 0, godot::Ref<godot::Image>());
	ERR_FAIL_COND_V(p_size.y < 0, godot::Ref<godot::Image>());

	godot::PackedByteArray buffer_f32_as_u8_pba;
	buffer_f32_as_u8_pba.resize(p_size.x * p_size.y * sizeof(float));
	Span<uint8_t> buffer_f32_as_u8(buffer_f32_as_u8_pba.ptrw(), buffer_f32_as_u8_pba.size());
	Span<float> buffer_f32 = buffer_f32_as_u8.reinterpret_cast_to<float>();

	Interval range;

	if (p_options.in_3d_space) {
		if (p_options.seamless) {
			ERR_PRINT("3D seamless noise is not supported");
			return godot::Ref<godot::Image>();
		} else {
			range = get_noise_3d_grid(godot::Vector3(), godot::Vector3i(p_size.x, p_size.y, 1), buffer_f32);
		}
	} else {
		if (p_options.seamless) {
			range = get_noise_2d_grid_tileable(p_size, buffer_f32);
		} else {
			range = get_noise_2d_grid(godot::Vector2(), p_size, buffer_f32);
		}
	}

	if (p_options.invert) {
		for (float &v : buffer_f32) {
			v = -v;
		}
	}

	if (p_options.normalize) {
		normalize(buffer_f32, range);
	}

	godot::Ref<godot::Image> image;

	switch (p_options.format) {
		case godot::Image::FORMAT_RF:
			image = godot::Image::create_from_data(p_size.x, p_size.y, false, p_options.format, buffer_f32_as_u8_pba);
			break;

		case godot::Image::FORMAT_R8:
		case godot::Image::FORMAT_L8: {
			const godot::PackedByteArray buffer_u8_pba = convert_f32_snorm_to_u8_packed_byte_array(buffer_f32);
			image = godot::Image::create_from_data(p_size.x, p_size.y, false, p_options.format, buffer_u8_pba);
		} break;

		default:
			ERR_PRINT("Format not supported");
			break;
	}

	return image;
}

godot::TypedArray<godot::Image> FastNoise2::get_image_3d_with_options_internal(
		const godot::Vector3i p_size,
		const ImageOptions p_options
) const {
	ERR_FAIL_COND_V(p_size.x < 0, godot::TypedArray<godot::Image>());
	ERR_FAIL_COND_V(p_size.y < 0, godot::TypedArray<godot::Image>());
	ERR_FAIL_COND_V(p_size.z < 0, godot::TypedArray<godot::Image>());

	godot::PackedByteArray buffer_f32_as_u8_pba;
	buffer_f32_as_u8_pba.resize(p_size.x * p_size.y * p_size.z * sizeof(float));
	Span<uint8_t> buffer_f32_as_u8(buffer_f32_as_u8_pba.ptrw(), buffer_f32_as_u8_pba.size());
	Span<float> buffer_f32 = buffer_f32_as_u8.reinterpret_cast_to<float>();

	Interval range;

	if (p_options.seamless) {
		ERR_PRINT("3D seamless noise is not supported");
		return godot::TypedArray<godot::Image>();
	} else {
		range = get_noise_3d_grid(godot::Vector3(), p_size, buffer_f32);
	}

	if (p_options.invert) {
		for (float &v : buffer_f32) {
			v = -v;
		}
	}

	if (p_options.normalize) {
		normalize(buffer_f32, range);
	}

	godot::TypedArray<godot::Image> images;
	images.resize(p_size.z);

	const unsigned int deck_size = p_size.x * p_size.y;

	switch (p_options.format) {
		case godot::Image::FORMAT_RF:
			for (int z = 0; z < p_size.z; ++z) {
				const Span<const float> deck = buffer_f32.sub(z * deck_size, deck_size);
				const godot::PackedByteArray image_bytes = reinterpret_f32_to_packed_byte_array(deck);
				const godot::Ref<godot::Image> image =
						godot::Image::create_from_data(p_size.x, p_size.y, false, p_options.format, image_bytes);
				images[z] = image;
			}
			break;

		case godot::Image::FORMAT_R8:
		case godot::Image::FORMAT_L8: {
			for (int z = 0; z < p_size.z; ++z) {
				const Span<const float> deck = buffer_f32.sub(z * deck_size, deck_size);
				const godot::PackedByteArray image_bytes = convert_f32_snorm_to_u8_packed_byte_array(deck);
				const godot::Ref<godot::Image> image =
						godot::Image::create_from_data(p_size.x, p_size.y, false, p_options.format, image_bytes);
				images[z] = image;
			}
		} break;

		default:
			ERR_PRINT("Format not supported");
			break;
	}

	return images;
}

godot::Ref<godot::Image> FastNoise2::get_image(
		int p_width,
		int p_height,
		bool p_invert,
		bool p_in_3d_space,
		bool p_normalize
) const {
	ImageOptions options;
	options.invert = p_invert;
	options.in_3d_space = p_in_3d_space;
	options.normalize = p_normalize;
	// To match Godot expectations
	options.format = godot::Image::FORMAT_L8;
	return get_image_with_options_internal(godot::Vector2i(p_width, p_height), options);
}

godot::TypedArray<godot::Image> FastNoise2::get_image_3d(
		int p_width,
		int p_height,
		int p_depth,
		bool p_invert,
		bool p_normalize
) const {
	ImageOptions options;
	options.invert = p_invert;
	options.normalize = p_normalize;
	// To match Godot expectations
	options.format = godot::Image::FORMAT_L8;
	return get_image_3d_with_options_internal(godot::Vector3i(p_width, p_height, p_depth), options);
}

godot::Ref<godot::Image> FastNoise2::get_seamless_image(
		int p_width,
		int p_height,
		bool p_invert,
		bool p_in_3d_space,
		real_t p_blend_skirt,
		bool p_normalize
) const {
	ImageOptions options;
	options.invert = p_invert;
	options.in_3d_space = p_in_3d_space;
	options.normalize = p_normalize;
	options.seamless = true;
	// To match Godot expectations
	options.format = godot::Image::FORMAT_L8;
	// Blend skirt is not used, it is not necessary.
	return get_image_with_options_internal(godot::Vector2i(p_width, p_height), options);
}

void FastNoise2::_bind_methods() {
	using namespace godot;
	using Self = FastNoise2;

	ClassDB::bind_method(D_METHOD("set_noise_type", "type"), &Self::set_noise_type);
	ClassDB::bind_method(D_METHOD("get_noise_type"), &Self::get_noise_type);

	ClassDB::bind_method(D_METHOD("set_seed", "seed"), &Self::set_seed);
	ClassDB::bind_method(D_METHOD("get_seed"), &Self::get_seed);

	ClassDB::bind_method(D_METHOD("set_period", "period"), &Self::set_period);
	ClassDB::bind_method(D_METHOD("get_period"), &Self::get_period);

	ClassDB::bind_method(D_METHOD("set_fractal_type", "type"), &Self::set_fractal_type);
	ClassDB::bind_method(D_METHOD("get_fractal_type"), &Self::get_fractal_type);

	ClassDB::bind_method(D_METHOD("set_fractal_octaves", "octaves"), &Self::set_fractal_octaves);
	ClassDB::bind_method(D_METHOD("get_fractal_octaves"), &Self::get_fractal_octaves);

	ClassDB::bind_method(D_METHOD("set_fractal_lacunarity", "lacunarity"), &Self::set_fractal_lacunarity);
	ClassDB::bind_method(D_METHOD("get_fractal_lacunarity"), &Self::get_fractal_lacunarity);

	ClassDB::bind_method(D_METHOD("set_fractal_gain", "gain"), &Self::set_fractal_gain);
	ClassDB::bind_method(D_METHOD("get_fractal_gain"), &Self::get_fractal_gain);

	ClassDB::bind_method(D_METHOD("set_fractal_ping_pong_strength", "strength"), &Self::set_fractal_ping_pong_strength);
	ClassDB::bind_method(D_METHOD("get_fractal_ping_pong_strength"), &Self::get_fractal_ping_pong_strength);

	// ClassDB::bind_method(
	// 		D_METHOD("set_fractal_weighted_strength", "strength"), &FastNoise2::set_fractal_weighted_strength);
	// ClassDB::bind_method(D_METHOD("get_fractal_weighted_strength"), &FastNoise2::get_fractal_weighted_strength);

	ClassDB::bind_method(
			D_METHOD("set_cellular_distance_function", "cell_distance_func"), &Self::set_cellular_distance_function
	);
	ClassDB::bind_method(D_METHOD("get_cellular_distance_function"), &Self::get_cellular_distance_function);

	ClassDB::bind_method(D_METHOD("set_cellular_return_type", "return_type"), &Self::set_cellular_return_type);
	ClassDB::bind_method(D_METHOD("get_cellular_return_type"), &Self::get_cellular_return_type);

	ClassDB::bind_method(D_METHOD("set_cellular_jitter", "return_type"), &Self::set_cellular_jitter);
	ClassDB::bind_method(D_METHOD("get_cellular_jitter"), &Self::get_cellular_jitter);

	// ClassDB::bind_method(D_METHOD("set_rotation_type_3d", "type"), &FastNoiseLite::set_rotation_type_3d);
	// ClassDB::bind_method(D_METHOD("get_rotation_type_3d"), &FastNoiseLite::get_rotation_type_3d);

	ClassDB::bind_method(D_METHOD("set_terrace_enabled", "enabled"), &Self::set_terrace_enabled);
	ClassDB::bind_method(D_METHOD("is_terrace_enabled"), &Self::is_terrace_enabled);

	ClassDB::bind_method(D_METHOD("set_terrace_multiplier", "multiplier"), &Self::set_terrace_multiplier);
	ClassDB::bind_method(D_METHOD("get_terrace_multiplier"), &Self::get_terrace_multiplier);

	ClassDB::bind_method(D_METHOD("set_terrace_smoothness", "smoothness"), &Self::set_terrace_smoothness);
	ClassDB::bind_method(D_METHOD("get_terrace_smoothness"), &Self::get_terrace_smoothness);

	ClassDB::bind_method(D_METHOD("set_remap_enabled", "enabled"), &Self::set_remap_enabled);
	ClassDB::bind_method(D_METHOD("is_remap_enabled"), &Self::is_remap_enabled);

	ClassDB::bind_method(D_METHOD("set_remap_input_min", "min_value"), &Self::set_remap_input_min);
	ClassDB::bind_method(D_METHOD("get_remap_input_min"), &Self::get_remap_input_min);

	ClassDB::bind_method(D_METHOD("set_remap_input_max", "max_value"), &Self::set_remap_input_max);
	ClassDB::bind_method(D_METHOD("get_remap_input_max"), &Self::get_remap_input_max);

	ClassDB::bind_method(D_METHOD("set_remap_output_min", "min_value"), &Self::set_remap_output_min);
	ClassDB::bind_method(D_METHOD("get_remap_output_min"), &Self::get_remap_output_min);

	ClassDB::bind_method(D_METHOD("set_remap_output_max", "max_value"), &Self::set_remap_output_max);
	ClassDB::bind_method(D_METHOD("get_remap_output_max"), &Self::get_remap_output_max);

	ClassDB::bind_method(D_METHOD("set_encoded_node_tree", "code"), &Self::set_encoded_node_tree);
	ClassDB::bind_method(D_METHOD("get_encoded_node_tree"), &Self::get_encoded_node_tree);

	ClassDB::bind_method(D_METHOD("get_noise_2d_single", "pos"), &Self::get_noise_2d_single);
	ClassDB::bind_method(D_METHOD("get_noise_3d_single", "pos"), &Self::get_noise_3d_single);

	ClassDB::bind_method(
			D_METHOD("get_image", "width", "height", "invert", "in_3d_space", "normalize"), &Self::get_image
	);
	ClassDB::bind_method(
			D_METHOD("get_image_3d", "width", "height", "depth", "invert", "normalize"), &Self::get_image_3d
	);

	ClassDB::bind_method(
			D_METHOD("get_seamless_image", "width", "height", "invert", "in_3d_space", "blend_skirt", "normalize"),
			&Self::get_seamless_image
	);

	ClassDB::bind_method(D_METHOD("get_simd_level_name", "level"), &Self::_b_get_simd_level_name);

	ClassDB::bind_method(D_METHOD("update_generator"), &Self::update_generator);

	// ClassDB::bind_method(D_METHOD("_on_warp_noise_changed"), &FastNoiseLite::_on_warp_noise_changed);

	ADD_PROPERTY(
			PropertyInfo(Variant::INT, "noise_type", PROPERTY_HINT_ENUM, NOISE_TYPE_HINT_STRING),
			"set_noise_type",
			"get_noise_type"
	);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "seed"), "set_seed", "get_seed");

	ADD_PROPERTY(
			PropertyInfo(Variant::FLOAT, "period", PROPERTY_HINT_RANGE, "0.0001,10000.0,0.1,exp"),
			"set_period",
			"get_period"
	);

	// ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "warp_noise", PROPERTY_HINT_RESOURCE_TYPE, "FastNoiseLiteGradient"),
	// 		"set_warp_noise", "get_warp_noise");

	ADD_GROUP("Fractal", "");

	ADD_PROPERTY(
			PropertyInfo(Variant::INT, "fractal_type", PROPERTY_HINT_ENUM, FRACTAL_TYPE_HINT_STRING),
			"set_fractal_type",
			"get_fractal_type"
	);

	ADD_PROPERTY(
			PropertyInfo(Variant::INT, "fractal_octaves", PROPERTY_HINT_RANGE, vformat("1,%d,1", MAX_OCTAVES)),
			"set_fractal_octaves",
			"get_fractal_octaves"
	);

	ADD_PROPERTY(
			PropertyInfo(Variant::FLOAT, "fractal_lacunarity"), "set_fractal_lacunarity", "get_fractal_lacunarity"
	);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "fractal_gain"), "set_fractal_gain", "get_fractal_gain");

	ADD_PROPERTY(
			PropertyInfo(Variant::FLOAT, "fractal_ping_pong_strength"),
			"set_fractal_ping_pong_strength",
			"get_fractal_ping_pong_strength"
	);

	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "fractal_weighted_strength"), "set_fractal_weighted_strength",
	// 		"get_fractal_weighted_strength");

	ADD_GROUP("Cellular", "");

	ADD_PROPERTY(
			PropertyInfo(
					Variant::INT,
					"cellular_distance_function",
					PROPERTY_HINT_ENUM,
					CELLULAR_DISTANCE_FUNCTION_HINT_STRING
			),
			"set_cellular_distance_function",
			"get_cellular_distance_function"
	);

	ADD_PROPERTY(
			PropertyInfo(Variant::INT, "cellular_return_type", PROPERTY_HINT_ENUM, CELLULAR_RETURN_TYPE_HINT_STRING),
			"set_cellular_return_type",
			"get_cellular_return_type"
	);

	ADD_PROPERTY(
			PropertyInfo(Variant::FLOAT, "cellular_jitter", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
			"set_cellular_jitter",
			"get_cellular_jitter"
	);

	ADD_GROUP("Terrace", "");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "terrace_enabled"), "set_terrace_enabled", "is_terrace_enabled");
	ADD_PROPERTY(
			PropertyInfo(Variant::FLOAT, "terrace_multiplier", PROPERTY_HINT_RANGE, "0.0,100.0,0.1"),
			"set_terrace_multiplier",
			"get_terrace_multiplier"
	);
	ADD_PROPERTY(
			PropertyInfo(Variant::FLOAT, "terrace_smoothness", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"),
			"set_terrace_smoothness",
			"get_terrace_smoothness"
	);

	ADD_GROUP("Remap", "");

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "remap_enabled"), "set_remap_enabled", "is_remap_enabled");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "remap_input_min"), "set_remap_input_min", "get_remap_input_min");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "remap_input_max"), "set_remap_input_max", "get_remap_input_max");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "remap_output_min"), "set_remap_output_min", "get_remap_output_min");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "remap_output_max"), "set_remap_output_max", "get_remap_output_max");

	ADD_GROUP("Advanced", "");

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "encoded_node_tree"), "set_encoded_node_tree", "get_encoded_node_tree");

	// ADD_PROPERTY(
	// 		PropertyInfo(Variant::INT, "rotation_type_3d", PROPERTY_HINT_ENUM, "None,ImproveXYPlanes,ImproveXZPlanes"),
	// 		"set_rotation_type_3d", "get_rotation_type_3d");

	BIND_ENUM_CONSTANT(TYPE_OPEN_SIMPLEX_2);
	BIND_ENUM_CONSTANT(TYPE_SIMPLEX);
	BIND_ENUM_CONSTANT(TYPE_PERLIN);
	BIND_ENUM_CONSTANT(TYPE_VALUE);
	BIND_ENUM_CONSTANT(TYPE_CELLULAR);
	BIND_ENUM_CONSTANT(TYPE_ENCODED_NODE_TREE);

	BIND_ENUM_CONSTANT(FRACTAL_NONE);
	BIND_ENUM_CONSTANT(FRACTAL_FBM);
	BIND_ENUM_CONSTANT(FRACTAL_RIDGED);
	BIND_ENUM_CONSTANT(FRACTAL_PING_PONG);

	// BIND_ENUM_CONSTANT(ROTATION_3D_NONE);
	// BIND_ENUM_CONSTANT(ROTATION_3D_IMPROVE_XY_PLANES);
	// BIND_ENUM_CONSTANT(ROTATION_3D_IMPROVE_XZ_PLANES);

	BIND_ENUM_CONSTANT(CELLULAR_DISTANCE_EUCLIDEAN);
	BIND_ENUM_CONSTANT(CELLULAR_DISTANCE_EUCLIDEAN_SQ);
	BIND_ENUM_CONSTANT(CELLULAR_DISTANCE_MANHATTAN);
	BIND_ENUM_CONSTANT(CELLULAR_DISTANCE_HYBRID);
	BIND_ENUM_CONSTANT(CELLULAR_DISTANCE_MAX_AXIS);

	BIND_ENUM_CONSTANT(CELLULAR_RETURN_INDEX_0);
	BIND_ENUM_CONSTANT(CELLULAR_RETURN_INDEX_0_ADD_1);
	BIND_ENUM_CONSTANT(CELLULAR_RETURN_INDEX_0_SUB_1);
	BIND_ENUM_CONSTANT(CELLULAR_RETURN_INDEX_0_MUL_1);
	BIND_ENUM_CONSTANT(CELLULAR_RETURN_INDEX_0_DIV_1);

	BIND_ENUM_CONSTANT(SIMD_NULL);
	BIND_ENUM_CONSTANT(SIMD_SCALAR);
	BIND_ENUM_CONSTANT(SIMD_SSE);
	BIND_ENUM_CONSTANT(SIMD_SSE2);
	BIND_ENUM_CONSTANT(SIMD_SSE3);
	BIND_ENUM_CONSTANT(SIMD_SSSE3);
	BIND_ENUM_CONSTANT(SIMD_SSE41);
	BIND_ENUM_CONSTANT(SIMD_SSE42);
	BIND_ENUM_CONSTANT(SIMD_AVX);
	BIND_ENUM_CONSTANT(SIMD_AVX2);
	BIND_ENUM_CONSTANT(SIMD_AVX512);
	BIND_ENUM_CONSTANT(SIMD_NEON);
}

} // namespace zylann
