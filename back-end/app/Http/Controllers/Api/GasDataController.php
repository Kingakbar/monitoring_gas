<?php

namespace App\Http\Controllers\Api;

use App\Models\GasData;
use Illuminate\Http\Request;
use App\Http\Controllers\Controller;

class GasDataController extends Controller
{
    /**
     * Display a listing of the resource.
     */
    public function index()
    {
        $gasData = GasData::latest()->first();
        return response()->json($gasData);
    }

    /**
     * Store a newly created resource in storage.
     */
    public function store(Request $request)
{
    // Validasi permintaan
    $request->validate([
        'gas_level' => 'required|numeric',
    ]);

    // Simpan data gas ke database
    $gasData = new GasData();
    $gasData->gas_level = $request->gas_level;
    $gasData->save();

    // Periksa apakah sudah ada 5 data
    if (GasData::count() > 5) {
        // Hapus 5 data terlama
        $this->deleteOldestGasData(5);
    }

    // Ambil data gas terbaru
    $latestGasData = $this->getLatestGasData();

    // Beri respons dengan data gas terbaru
    return response()->json($latestGasData, 201);
}

/**
 * Delete the oldest gas data.
 *
 * @param int $count
 * @return void
 */
private function deleteOldestGasData($count)
{
    // Hapus data yang paling lama sesuai jumlah yang ditentukan
    GasData::orderBy('created_at')->limit($count)->delete();
}


private function getLatestGasData()
{
    return GasData::latest()->first();
}


    /**
     * Display the specified resource.
     */
    public function show(string $id)
    {
        //
    }

    /**
     * Update the specified resource in storage.
     */
    public function update(Request $request, string $id)
    {
        //
    }

    /**
     * Remove the specified resource from storage.
     */
    public function destroy(string $id)
    {
        //
    }
}
