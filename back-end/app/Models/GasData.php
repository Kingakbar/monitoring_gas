<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class GasData extends Model
{
    use HasFactory;

    protected $table = 'gasdata';
    protected $fillable = [
      'gas_level',
    ];
}
