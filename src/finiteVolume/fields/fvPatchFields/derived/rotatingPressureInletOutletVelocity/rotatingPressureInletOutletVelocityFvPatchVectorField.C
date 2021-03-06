/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "rotatingPressureInletOutletVelocityFvPatchVectorField.H"
#include "addToRunTimeSelectionTable.H"
#include "volFields.H"
#include "surfaceFields.H"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::rotatingPressureInletOutletVelocityFvPatchVectorField::
calcTangentialVelocity()
{
    vector axisHat = omega_/mag(omega_);
    const vectorField tangentialVelocity
    (
        (-omega_) ^ (patch().Cf() - axisHat*(axisHat & patch().Cf()))
    );

    const vectorField n(patch().nf());
    refValue() = tangentialVelocity - n*(n & tangentialVelocity);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::rotatingPressureInletOutletVelocityFvPatchVectorField::
rotatingPressureInletOutletVelocityFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF
)
:
    pressureInletOutletVelocityFvPatchVectorField(p, iF),
    omega_(vector::zero)
{}


Foam::rotatingPressureInletOutletVelocityFvPatchVectorField::
rotatingPressureInletOutletVelocityFvPatchVectorField
(
    const rotatingPressureInletOutletVelocityFvPatchVectorField& ptf,
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    pressureInletOutletVelocityFvPatchVectorField(ptf, p, iF, mapper),
    omega_(ptf.omega_)
{
    calcTangentialVelocity();
}


Foam::rotatingPressureInletOutletVelocityFvPatchVectorField::
rotatingPressureInletOutletVelocityFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const dictionary& dict
)
:
    pressureInletOutletVelocityFvPatchVectorField(p, iF, dict),
    omega_(dict.lookup("omega"))
{
    calcTangentialVelocity();
}


Foam::rotatingPressureInletOutletVelocityFvPatchVectorField::
rotatingPressureInletOutletVelocityFvPatchVectorField
(
    const rotatingPressureInletOutletVelocityFvPatchVectorField& pivpvf
)
:
    pressureInletOutletVelocityFvPatchVectorField(pivpvf),
    omega_(pivpvf.omega_)
{
    calcTangentialVelocity();
}


Foam::rotatingPressureInletOutletVelocityFvPatchVectorField::
rotatingPressureInletOutletVelocityFvPatchVectorField
(
    const rotatingPressureInletOutletVelocityFvPatchVectorField& pivpvf,
    const DimensionedField<vector, volMesh>& iF
)
:
    pressureInletOutletVelocityFvPatchVectorField(pivpvf, iF),
    omega_(pivpvf.omega_)
{
    calcTangentialVelocity();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::rotatingPressureInletOutletVelocityFvPatchVectorField::write
(
    Ostream& os
) const
{
    fvPatchVectorField::write(os);
    os.writeKeyword("phi") << phiName() << token::END_STATEMENT << nl;
    os.writeKeyword("omega")<< omega_ << token::END_STATEMENT << nl;
    writeEntry("value", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    makePatchTypeField
    (
        fvPatchVectorField,
        rotatingPressureInletOutletVelocityFvPatchVectorField
    );
}

// ************************************************************************* //
